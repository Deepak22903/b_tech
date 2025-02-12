import bs4
import requests
import os

class GitHub_User_Config_Scraper:
    def __init__(self, username):
        self.username = username
        self.url = f'https://github.com/{self.username}'

    def get_user_config(self):
        response = requests.get(self.url)
        soup = bs4.BeautifulSoup(response.text, 'html.parser')
        print(soup)
        return soup
    
    def get_user_config_image(self):
        user_config = self.get_user_config()
        user_config_image = user_config.find(class_='avatar avatar-user width-full border color-bg-default')

        # Download the image
        try:
            os.mkdir(self.username)
        except FileExistsError:
            pass

        image_link = user_config_image['src']
        image = requests.get(image_link)
        with open(f'{self.username}/dp.png', 'wb') as f:
            f.write(image.content)
        print("Profile Photo downloaded successfully!\n")

        return user_config_image
    

if __name__ == '__main__':
    while True:
        username = input("Enter the username: ")

        if username == '':
            print("Please enter a valid username")
        else:
            user = GitHub_User_Config_Scraper(username)
            user.get_user_config_image()
    