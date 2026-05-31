import webview
import tkinter as tk
from tkinter import messagebox

# Default ESP8266 IP address from your firmware code
DEFAULT_IP = "192.168.0.166"

def launch_dashboard(ip_address):
    """Launches the native desktop window pointing to the ESP8266."""
    # Ensure the URL has the correct HTTP prefix
    if not ip_address.startswith("http://") and not ip_address.startswith("https://"):
        target_url = f"http://{ip_address}"
    else:
        target_url = ip_address

    print(f"Connecting to PEMS Server at: {target_url}")
    
    # Open the native Windows GUI window
    webview.create_window(
        title="🍀 PEMS - Plant Environment Management System",
        url=target_url,
        width=1000,
        height=750,
        resizable=True,
        min_size=(400, 600)
    )
    webview.start()

def create_login_gui():
    """Creates a lightweight launcher window to configure the IP network."""
    root = tk.Tk()
    root.title("PEMS Launcher")
    root.geometry("360x220")
    root.configure(bg="#121212")
    root.resizable(False, False)

    # Title Label
    title_label = tk.Label(
        root, 
        text="PEMS Desktop Controller", 
        font=("Segoe UI", 14, "bold"), 
        bg="#121212", 
        fg="#ffffff"
    )
    title_label.pack(pady=15)

    # Subtext
    info_label = tk.Label(
        root, 
        text="Enter your ESP8266 IP Address:", 
        font=("Segoe UI", 10), 
        bg="#121212", 
        fg="#aaaaaa"
    )
    info_label.pack(pady=2)

    # IP Entry Field
    ip_entry = tk.Entry(
        root, 
        font=("Segoe UI", 12), 
        justify="center", 
        bg="#1e1e1e", 
        fg="#ffffff", 
        insertbackground="white", 
        bd=1, 
        relief="solid"
    )
    ip_entry.insert(0, DEFAULT_IP)
    ip_entry.pack(pady=10, ipady=4, ipadx=10)

    def on_submit():
        ip = ip_entry.get().strip()
        if not ip:
            messagebox.showerror("Error", "IP Address field cannot be empty.")
            return
        root.destroy()  # Close the launcher window
        launch_dashboard(ip)  # Start the main controller interface

    # Connect Button
    connect_btn = tk.Button(
        root, 
        text="Connect to Panel", 
        font=("Segoe UI", 11, "bold"), 
        bg="#00bfff", 
        fg="#ffffff", 
        activebackground="#0077cc", 
        activeforeground="#ffffff",
        bd=0, 
        cursor="hand2", 
        command=on_submit
    )
    connect_btn.pack(pady=15, ipadx=20, ipady=6)

    root.mainloop()

if __name__ == "__main__":
    create_login_gui()