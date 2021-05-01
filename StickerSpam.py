#import stuff
from selenium import webdriver
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By
import time

# set variables
target='"Friend"' #contact or group name where you want to send messages (make sure to not mess with the quotes)
times_scroll = 6 #refer delimiter comment below
times_repeat = 100 #refer delimiter comment below
chromeDriverLocation = "D:\Downloads\chromedriver.exe" #change it with location where you saved chrome driver (most likely downloads folder)

#actual code
driver=webdriver.Chrome(chromeDriverLocation) #opens chrome
driver.get("https://web.whatsapp.com/") #opens whatsapp web, you'll have to manually scan qr code to login
wait=WebDriverWait(driver,600)
x_arg='//span[contains(@title, '+target+')]'
target=wait.until(EC.presence_of_element_located((By.XPATH, x_arg))) #stores location of chat of target
target.click() #open target chat (Note: if chat doesn't open, try scrolling on the automated browser to bring target contact to view)

emojimenu=wait.until(EC.presence_of_element_located((By.XPATH,'//*[@id="main"]/footer/div[1]/div[1]/div[1]')))
emojimenu.click() #opens emoji menu
stickermenu=wait.until(EC.presence_of_element_located((By.XPATH, '//*[@id="main"]/footer/div[1]/div[1]/div[1]/button[4]')))
stickermenu.click() #opens sticker menu
x_arg_begin = '//*[@id="main"]/footer/div[2]/div/div[3]/div[1]/div/div[1]/div[2]/div/div['
x_arg_end=']/div/span/img'

"""
So how do the stickers get selected?
basically, the first menu to pop up in the stickers menu is the recent stickers used one. 
We'll be spamming few recent ones. 
The first (and the most recent) sticker has div[1], the second has div[2] and so on. 

Now we can technically run a loop till *x* recent stickers but stickers that are not visible in the browser won't send unless you manually scroll.
And manually scrolling everytime can be a pain. 
So, I have initialised 3 nested loops that send 4 stickers at a time, for the number of times you  want to send each sticker aka times_repeat and a total of times_scroll*4 stickers sent times_repeat times.

If you want to collate, shift the second loop with the third loop (collate means if you want each sticker to be sent times_repeat times before the new sticker is sent.)
"""

for i in range(times_scroll): #times scroll
    for a in range(times_repeat): #times repeat
        for j in range(1,5): #times send
            sticker=wait.until(EC.presence_of_element_located((By.XPATH, x_arg_begin+str((times_scroll*i)+j)+x_arg_end)))
            sticker.click()