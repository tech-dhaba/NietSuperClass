import sys
import serial
import threading
import numpy as np
from PyQt6.QtWidgets import QApplication, QMainWindow, QPushButton, QVBoxLayout, QWidget, QLabel, QLineEdit, QTextEdit
from PyQt6.QtCore import QTimer, Qt, pyqtSignal, QObject
import pyqtgraph as pg

class UARTWorker(QObject):
    data_received = pyqtSignal(bytes)

    def __init__(self):
        super().__init__()
        self.serial_port = None
        self.is_running = False

    def start(self, port='COM8', baudrate=9600):
        if self.serial_port is None:
            try:
                self.serial_port = serial.Serial(port=port, baudrate=baudrate, timeout=0.1)
                self.is_running = True
                self.worker_thread = threading.Thread(target=self.run, daemon=True)
                self.worker_thread.start()
            except serial.SerialException as e:
                print(f'Error: {e}')

    def stop(self):
        if self.serial_port is not None:
            self.is_running = False
            self.serial_port.close()
            self.serial_port = None

    def run(self):
        while self.is_running:
            if self.serial_port.in_waiting > 0:
                data = self.serial_port.read(1)  # Read one byte from the UART
                self.data_received.emit(data)

class UARTVisualizer(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()
        self.worker = UARTWorker()
        self.worker.data_received.connect(self.process_data)

        self.update_interval = 100  # milliseconds
        self.timer = QTimer()
        self.timer.timeout.connect(self.update_plot)
        self.timer.start(self.update_interval)

        self.bits = np.zeros(8, dtype=int)
        self.current_character = None

    def initUI(self):
        self.setWindowTitle('UART Visualizer')
        self.setGeometry(100, 100, 800, 600)
        self.setStyleSheet("background-color: #2e2e2e; color: #ffffff;")

        self.plot_widget = pg.PlotWidget()
        self.plot_widget.setLabel('left', 'Bit Value')
        self.plot_widget.setLabel('bottom', 'Bit Position')
        self.plot_widget.setRange(xRange=[0, 8], yRange=[-0.1, 1.1])
        self.plot_widget.setStyleSheet("background-color: #1e1e1e;")

        self.plot_curve = self.plot_widget.plot(pen='g')

        self.text_display = QTextEdit()
        self.text_display.setReadOnly(True)
        self.text_display.setStyleSheet("background-color: #2d2d2d; border: 1px solid #444; color: #ffffff; padding: 10px;")

        self.bit_display = QLabel()
        self.bit_display.setStyleSheet("color: #9cdcfe; padding: 5px;")

        self.status_label = QLabel('Status: Disconnected')
        self.status_label.setStyleSheet("color: #ff5555; padding: 5px;")

        self.start_button = QPushButton('Start')
        self.stop_button = QPushButton('Stop')
        self.clear_button = QPushButton('Clear')
        self.send_button = QPushButton('Send Data')

        self.data_input = QLineEdit()
        self.data_input.setPlaceholderText('Enter data to send...')

        self.start_button.clicked.connect(self.start_acquisition)
        self.stop_button.clicked.connect(self.stop_acquisition)
        self.clear_button.clicked.connect(self.clear_display)
        self.send_button.clicked.connect(self.send_data)

        layout = QVBoxLayout()
        layout.addWidget(self.plot_widget)
        layout.addWidget(self.text_display)
        layout.addWidget(self.bit_display)
        layout.addWidget(self.status_label)
        layout.addWidget(self.data_input)
        layout.addWidget(self.start_button)
        layout.addWidget(self.stop_button)
        layout.addWidget(self.clear_button)
        layout.addWidget(self.send_button)

        container = QWidget()
        container.setLayout(layout)

        self.setCentralWidget(container)

    def start_acquisition(self):
        self.worker.start(port='COM8', baudrate=9600)
        self.status_label.setText('Status: Connected')

    def stop_acquisition(self):
        self.worker.stop()
        self.status_label.setText('Status: Disconnected')

    def process_data(self, data):
        bit_representation = f'{ord(data):08b}'  # Convert to 8-bit binary

        self.current_character = data.decode('ascii', errors='ignore')
        bit_display_text = f'Byte: {self.current_character} ({bit_representation})'
        self.bit_display.setText(bit_display_text)

        self.bits = np.array([int(bit) for bit in bit_representation])
        self.update_display()

    def update_display(self):
        self.text_display.setPlainText(self.current_character)
        self.update_plot()

    def update_plot(self):
        step_x = []
        step_y = []

        for i, bit in enumerate(self.bits):
            step_x.extend([i, i + 1])
            step_y.extend([bit, bit])

        self.plot_curve.setData(step_x, step_y)

    def clear_display(self):
        self.text_display.clear()
        self.bit_display.setText('Current Byte:')
        self.bits = np.zeros(8, dtype=int)
        self.plot_curve.setData([], [])

    def send_data(self):
        if self.worker.serial_port and self.data_input.text():
            self.worker.serial_port.write(self.data_input.text().encode('ascii'))
            self.data_input.clear()

def run_app():
    app = QApplication(sys.argv)
    window = UARTVisualizer()
    window.show()
    sys.exit(app.exec())

if __name__ == '__main__':
    run_app()

