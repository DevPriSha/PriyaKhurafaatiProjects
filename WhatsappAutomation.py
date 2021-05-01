#import modules
from selenium import webdriver
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By
import time

#set variables
target='"Friend"' #contact or group name where you want to send messages (make sure to not mess with the quotes)
chromeDriverLocation = "D:\Downloads\chromedriver.exe" #change it with location where you saved chrome driver (most likely downloads folder)
stringStart=' This group has been hacked. It will now be deleted after  ' #beginning of message
stringEnd=" messages Σ3" #ending of message
textBoxClassName = "_2A8P4" #different for different users, use inspect elements to find yours
timesSpam = 1000 #number of times a message should be spammed

#actual code
driver=webdriver.Chrome(chromeDriverLocation) #opens chrome
driver.get("https://web.whatsapp.com/") #opens whatsapp web, you'll have to manually scan qr code to login
wait=WebDriverWait(driver,600)
x_arg='//span[contains(@title, '+target+')]' 
target=wait.until(EC.presence_of_element_located((By.XPATH, x_arg))) #stores location of chat of target
target.click() #open target chat (Note: if chat doesn't open, try scrolling on the automated browser to bring target contact to view)

input_box=driver.find_element_by_class_name(textBoxClassName) 

for i in range(timesSpam):
    input_box.send_keys(string+str(timesSpam-i)+string2+Keys.ENTER) #you can set this acc to your tastes. DO NOT REMOVE +Keys.ENTER