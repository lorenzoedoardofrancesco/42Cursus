from flask import Flask, render_template
import requests

app = Flask(__name__)

CAT_API_URL = "https://api.thecatapi.com/v1/images/search"

@app.route('/')
def index():
    response = requests.get(CAT_API_URL)
    if response.status_code == 200:
        data = response.json()
        if data:
            cat_image_url = data[0]['url']
            return render_template('index.html', cat_image_url=cat_image_url)
    
    return "Failed to fetch cat image."

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=80)
