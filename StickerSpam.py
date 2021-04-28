from selenium import webdriver
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By
import time

driver=webdriver.Chrome("D:\Downloads\chromedriver.exe")
driver.get("https://web.whatsapp.com/")
wait=WebDriverWait(driver,600)
target='"+91 80103 56367"'
x_arg='//span[contains(@title, '+target+')]'
target=wait.until(EC.presence_of_element_located((By.XPATH, x_arg)))
target.click()

emojimenu=wait.until(EC.presence_of_element_located((By.XPATH,'//*[@id="main"]/footer/div[1]/div[1]/div[1]')))
emojimenu.click()
stickermenu=wait.until(EC.presence_of_element_located((By.XPATH, '//*[@id="main"]/footer/div[1]/div[1]/div[1]/button[4]')))
stickermenu.click()
x_arg_begin = '//*[@id="main"]/footer/div[2]/div/div[3]/div[1]/div/div[1]/div[2]/div/div['
x_arg_end=']/div/span/img'

for i in range(6): #times scroll
    for a in range(2): #times repeat
        for j in range(1,5): #times send
            sticker=wait.until(EC.presence_of_element_located((By.XPATH, x_arg_begin+str(6*i+j)+x_arg_end)))
            sticker.click()