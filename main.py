# import all neede libraries and modules
import serial
import pandas as pd
import smtplib

# a simple function for mail sending
def send_mail():
    SenderAddress = "Sender Email"
    password = "Sender Password"

    subject = "KSEB NOtification"
    msg = "The power is temporarily down please stay with us our Employees is working on it.\n"

    # if users want to send mail to multiple users from excel sheet then uncomment the below lines
    # e = pd.read_excel("data.xlsx")
    # emails = (e['Email'].values)

    # else if you want to send mail without excel sheet then Give the email address of the user in the below line
    emails = ('mail2@mail.com', 'mail1@mail.com')
    # create a server object with gmail smtp server
    server = smtplib.SMTP("smtp.gmail.com", 587)
    # start TLS for security
    server.starttls()
    # login with sender email and password
    server.login(SenderAddress, password)
    # create the message
    body = "Subject: {}\n\n{}".format(subject,msg)
    # send mail to all the users in the list
    for email in emails:
        server.sendmail(SenderAddress, email, body)
    # end the session
    server.quit()


# create a function for main
def main(): 
    # The below code is always checking for the power status
    while True:
        # create a serial object with the port name and baud rate
        with serial.Serial('/dev/ttyACM0', 9600, timeout=1) as ser:
            # read the data from the serial port
            s = ser.read(10)
            # print the data
            print("listening:",s)
            # close the serial port
            ser.close()
        # if the power is down the serial port write [n] then send the mail
        if 'n' in str(s):
            print("Oooh Unexpected power gone for some moments")
            send_mail()
            print("mail sent")
            # wait for the power to come back
            while 'n' in str(s):
                print("waiting for power to come back")
                with serial.Serial('/dev/ttyACM0', 9600, timeout=5) as ser:
                    s = ser.read(10)
                    ser.close()
                    if 'n' in str(s):
                        pass
                    else:
                        # if the power is back then print the message and break the loop
                        print("power is back")
                        break



main()