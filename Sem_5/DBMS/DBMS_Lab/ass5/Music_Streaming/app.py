from flask import Flask, render_template, request, redirect, url_for
import mariadb

app = Flask(__name__)

# Database connection setup
def get_db_connection():
    try:
        conn = mariadb.connect(
            user="root",
            password="Deepak@22",
            host="localhost",
            port=3306,
            database="Music_Streaming"
        )
        return conn
    except mariadb.Error as e:
        print(f"Error connecting to MariaDB: {e}")
        return None

# Route to display the data and form
@app.route("/")
def index():
    conn = get_db_connection()
    cursor = conn.cursor()

    # Fetch data from all tables
    cursor.execute("SELECT * FROM Listener")
    listeners = cursor.fetchall()
    
    cursor.execute("SELECT * FROM Artist")
    artists = cursor.fetchall()

    cursor.execute("SELECT * FROM Song")
    songs = cursor.fetchall()

    cursor.execute("SELECT * FROM Playlist")
    playlists = cursor.fetchall()

    cursor.execute("SELECT * FROM PlayHistory")
    play_history = cursor.fetchall()

    cursor.execute("SELECT * FROM PlaylistSong")
    playlist_songs = cursor.fetchall()

    conn.close()
    return render_template("index.html", listeners=listeners, artists=artists, songs=songs,
                           playlists=playlists, play_history=play_history, playlist_songs=playlist_songs)

# Route to add a listener
@app.route("/add_listener", methods=["POST"])
def add_listener():
    conn = get_db_connection()
    cursor = conn.cursor()
    listener_name = request.form["listener_name"]
    email = request.form["email"]
    cursor.execute("INSERT INTO Listener (ListenerName, Email) VALUES (?, ?)", (listener_name, email))
    conn.commit()
    conn.close()
    return redirect(url_for("index"))

# Route to delete a listener
@app.route("/delete_listener/<int:id>")
def delete_listener(id):
    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute("DELETE FROM Listener WHERE ListenerID = ?", (id,))
    conn.commit()
    conn.close()
    return redirect(url_for("index"))

# Route to add an artist
@app.route("/add_artist", methods=["POST"])
def add_artist():
    conn = get_db_connection()
    cursor = conn.cursor()
    artist_name = request.form["artist_name"]
    cursor.execute("INSERT INTO Artist (ArtistName) VALUES (?)", (artist_name,))
    conn.commit()
    conn.close()
    return redirect(url_for("index"))

# Route to delete an artist
@app.route("/delete_artist/<int:id>")
def delete_artist(id):
    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute("DELETE FROM Artist WHERE ArtistID = ?", (id,))
    conn.commit()
    conn.close()
    return redirect(url_for("index"))

# Route to add a song
@app.route("/add_song", methods=["POST"])
def add_song():
    conn = get_db_connection()
    cursor = conn.cursor()
    song_name = request.form["song_name"]
    artist_id = request.form["artist_id"]
    cursor.execute("INSERT INTO Song (SongName, ArtistID) VALUES (?, ?)", (song_name, artist_id))
    conn.commit()
    conn.close()
    return redirect(url_for("index"))

# Route to delete a song
@app.route("/delete_song/<int:id>")
def delete_song(id):
    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute("DELETE FROM Song WHERE SongID = ?", (id,))
    conn.commit()
    conn.close()
    return redirect(url_for("index"))

# Route to add a playlist
@app.route("/add_playlist", methods=["POST"])
def add_playlist():
    conn = get_db_connection()
    cursor = conn.cursor()
    playlist_name = request.form["playlist_name"]
    listener_id = request.form["listener_id"]
    cursor.execute("INSERT INTO Playlist (PlaylistName, ListenerID) VALUES (?, ?)", (playlist_name, listener_id))
    conn.commit()
    conn.close()
    return redirect(url_for("index"))

# Route to delete a playlist
@app.route("/delete_playlist/<int:id>")
def delete_playlist(id):
    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute("DELETE FROM Playlist WHERE PlaylistID = ?", (id,))
    conn.commit()
    conn.close()
    return redirect(url_for("index"))

# Route to add a play history
@app.route("/add_play_history", methods=["POST"])
def add_play_history():
    conn = get_db_connection()
    cursor = conn.cursor()
    listener_id = request.form["listener_id"]
    song_id = request.form["song_id"]
    play_date = request.form["play_date"]
    cursor.execute("INSERT INTO PlayHistory (ListenerID, SongID, PlayDate) VALUES (?, ?, ?)", 
                   (listener_id, song_id, play_date))
    conn.commit()
    conn.close()
    return redirect(url_for("index"))

# Route to delete a play history record
@app.route("/delete_play_history/<int:listener_id>/<int:song_id>/<string:play_date>")
def delete_play_history(listener_id, song_id, play_date):
    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute("DELETE FROM PlayHistory WHERE ListenerID = ? AND SongID = ? AND PlayDate = ?", 
                   (listener_id, song_id, play_date))
    conn.commit()
    conn.close()
    return redirect(url_for("index"))

# Route to add a song to a playlist
@app.route("/add_playlist_song", methods=["POST"])
def add_playlist_song():
    conn = get_db_connection()
    cursor = conn.cursor()
    playlist_id = request.form["playlist_id"]
    song_id = request.form["song_id"]
    cursor.execute("INSERT INTO PlaylistSong (PlaylistID, SongID) VALUES (?, ?)", (playlist_id, song_id))
    conn.commit()
    conn.close()
    return redirect(url_for("index"))

# Route to delete a song from a playlist
@app.route("/delete_playlist_song/<int:playlist_id>/<int:song_id>")
def delete_playlist_song(playlist_id, song_id):
    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute("DELETE FROM PlaylistSong WHERE PlaylistID = ? AND SongID = ?", (playlist_id, song_id))
    conn.commit()
    conn.close()
    return redirect(url_for("index"))

if __name__ == "__main__":
    app.run(debug=True)
