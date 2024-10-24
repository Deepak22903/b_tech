
from flask import Flask, render_template, jsonify
import mariadb

app = Flask(__name__)

# Database connection (MariaDB)
conn = mariadb.connect(
    user="root",
    password="Deepak@22",
    host="localhost",
    port=3306,
    database="Music_Streaming_db"
)

cursor = conn.cursor()

# Route for homepage
@app.route('/')
def home():
    return render_template('home.html')

# Route to get all listeners
@app.route('/listeners')
def get_listeners():
    query = "SELECT * FROM Listener"
    cursor.execute(query)
    listeners = cursor.fetchall()
    return render_template('listeners.html', listeners=listeners)

# Route to get all songs
@app.route('/songs')
def get_songs():
    query = "SELECT * FROM Song"
    cursor.execute(query)
    songs = cursor.fetchall()
    return render_template('songs.html', songs=songs)

# Route for API endpoint to get listeners (as JSON)
@app.route('/api/listeners')
def api_get_listeners():
    query = "SELECT * FROM Listener"
    cursor.execute(query)
    listeners = cursor.fetchall()
    return jsonify(listeners)

if __name__ == "__main__":
    app.run(debug=True)
