from selenium import webdriver
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By
import time
driver=webdriver.Chrome("D:\Downloads\chromedriver.exe")
driver.get("https://web.whatsapp.com/")
wait=WebDriverWait(driver,600)
target='"CSAI 20 Shweta"'
string = 'HI! I am Priya. I love Olivia <3'
x_arg='//span[contains(@title, '+target+')]'
target=wait.until(EC.presence_of_element_located((By.XPATH, x_arg)))
target.click()

input_box=driver.find_element_by_class_name("_2A8P4")

for i in range(5):
    input_box.send_keys(string+Keys.ENTER)