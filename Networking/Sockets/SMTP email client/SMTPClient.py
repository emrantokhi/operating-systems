from socket import *
msg = "\r\nHello there!"
endmsg = "\r\n.\r\n"
mailServer = 'gaia.ecs.csus.edu'
#creating client socket to establish tcp conncetion with mail server
serverPort = 25
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((mailServer, serverPort))
recv = clientSocket.recv(1024)
print recv
if recv[:3] != '220':
            print '220 reply not received from server.'
#send helo command and print server response
heloCommand = 'HELO there\r\n'
clientSocket.send(heloCommand)
recv1 = clientSocket.recv(1024)
print recv1
if recv1[:3] != '250':
        print '250 reply not received from server.'
#send mail from command and print server response
mailFromCommand = 'MAIL FROM: <tokhie@ecs.csus.edu> \r\n'
clientSocket.send(mailFromCommand)
recv2 = clientSocket.recv(1024)
print(recv2)
if recv2[:3] != '250':
        print '250 reply not received from server'
#send RCPT TO command and print server response
recipient = raw_input("Enter a recipient's email: ")
rcptToCommand = 'RCPT TO: <' + recipient + ' > \r\n'
clientSocket.send(rcptToCommand)
recv3 = clientSocket.recv(1024)
print(recv3)
if recv3[:3] != '250':
        print '250 reply not received from server'
#send DATA command and print server response
dataCommand = 'DATA\r\n'
clientSocket.send(dataCommand)
recv4 = clientSocket.recv(1024)
print(recv4)
if recv4[:3] != '354':
        print '354 reply not received from server'
#send message data
subject = raw_input("Enter a subject: ")
subjectCmd = "Subject: "
subject = subjectCmd + subject + "\r\n\r\n"
clientSocket.send(subject)
message = raw_input("Enter a message: ")
print(endmsg)
clientSocket.send(message)
clientSocket.send(endmsg)
recv5 = clientSocket.recv(1024)
print (recv5)
#Quit the connection and close
clientSocket.send("QUIT\r\n")
recv6 = clientSocket.recv(1024)
print(recv6)
clientSocket.close
