from flask import Flask, render_template, request, redirect, url_for, session, flash
import mariadb
from werkzeug.security import generate_password_hash, check_password_hash

app = Flask(__name__)
app.secret_key = "515e5d26aad42bd157a913173e464b17"  # Set a secret key for session management

# Database connection setup
def get_db_connection():
    try:
        conn = mariadb.connect(
            user="root",
            password="Deepak@22",
            host="localhost",
            port=3306,
            database="Music_streaming_test"
        )
        return conn
    except mariadb.Error as e:
        print(f"Error connecting to MariaDB: {e}")
        return None

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        listener_name = request.form["listener_name"]  # Add this field to your registration form
        username = request.form["username"]
        email = request.form["email"]
        password = request.form["password"]
        
        conn = get_db_connection()
        cursor = conn.cursor()
        try:
            cursor.execute(
                "INSERT INTO Listener (ListenerName, Username, Email, Password) VALUES (?, ?, ?, ?)", 
                (listener_name, username, email, password)
            )
            conn.commit()
            flash("Registration successful! Please log in.")
            return redirect(url_for("login"))
        except mariadb.IntegrityError:
            flash("Username or email already exists.")
        finally:
            conn.close()
    
    return render_template("register.html")

# Login Route
@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        
        conn = get_db_connection()
        cursor = conn.cursor()
        cursor.execute("SELECT ListenerID, Password FROM Listener WHERE Username = ?", (username,))
        user = cursor.fetchone()
        conn.close()

        if user:
            stored_password = user[1]  # The password stored in the database (plain text)

            # Check if the input password matches the stored password
            if stored_password == password:
                session["user_id"] = user[0]
                session["username"] = username
                flash("Login successful!")
                return redirect(url_for("index"))  # Redirect to the index page after successful login
            else:
                flash("Invalid username or password.")
        else:
            flash("Invalid username or password.")
    
    return render_template("login.html")  # Always render the login page when GET request or failed login

@app.route("/logout", methods=["POST"])
def logout():
    session.clear()  # Clears the session
    flash("You have been logged out.")
    return redirect(url_for("login"))  # Redirect back to the login page

# Route to display the data and form
@app.route("/")
def index():
    if "user_id" not in session:  # If the user is not logged in
        return redirect(url_for("login"))  # Redirect to the login page if not logged in
    
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


# Route to update a listener
@app.route("/update_listener/<int:id>", methods=["GET", "POST"])
def update_listener(id):
    conn = get_db_connection()
    cursor = conn.cursor()
    
    if request.method == "POST":
        # Fetch updated data from form
        listener_name = request.form["listener_name"]
        email = request.form["email"]
        
        # Update the listener in the database
        cursor.execute("UPDATE Listener SET ListenerName = ?, Email = ? WHERE ListenerID = ?", (listener_name, email, id))
        conn.commit()
        conn.close()
        
        flash("Listener updated successfully!")
        return redirect(url_for("index"))
    
    # Fetch existing listener data to pre-fill the form
    cursor.execute("SELECT ListenerID, ListenerName, Email FROM Listener WHERE ListenerID = ?", (id,))
    listener = cursor.fetchone()
    conn.close()
    
    return render_template("update_listener.html", listener=listener)


# Route to update an artist
@app.route("/update_artist/<int:id>", methods=["GET", "POST"])
def update_artist(id):
    conn = get_db_connection()
    cursor = conn.cursor()
    
    if request.method == "POST":
        # Fetch updated data from form
        artist_name = request.form["artist_name"]
        
        # Update the artist in the database
        cursor.execute("UPDATE Artist SET ArtistName = ? WHERE ArtistID = ?", (artist_name, id))
        conn.commit()
        conn.close()
        
        flash("Artist updated successfully!")
        return redirect(url_for("index"))
    
    # Fetch existing artist data to pre-fill the form
    cursor.execute("SELECT ArtistID, ArtistName FROM Artist WHERE ArtistID = ?", (id,))
    artist = cursor.fetchone()
    conn.close()
    
    return render_template("update_artist.html", artist=artist)

@app.route('/update_song/<int:song_id>', methods=['GET', 'POST'])
def update_song(song_id):
    conn = get_db_connection()
    cursor = conn.cursor()

    # Fetch the song by its ID
    cursor.execute("SELECT SongID, SongName, ArtistID FROM Song WHERE SongID = ?", (song_id,))
    song = cursor.fetchone()

    # Fetch all artists for the dropdown list
    cursor.execute("SELECT ArtistID, ArtistName FROM Artist")
    artists = cursor.fetchall()

    if request.method == 'POST':
        song_name = request.form['song_name']
        artist_id = request.form['artist_id']

        # Update the song in the database
        cursor.execute("UPDATE Song SET SongName = ?, ArtistID = ? WHERE SongID = ?", 
                       (song_name, artist_id, song_id))
        conn.commit()
        conn.close()

        flash("Song updated successfully!")
        return redirect(url_for('index'))  # Redirect to the index page or another page as needed

    conn.close()
    return render_template('update_song.html', song=song, artists=artists)

@app.route('/update_playlist/<int:playlist_id>', methods=['GET', 'POST'])
def update_playlist(playlist_id):
    conn = get_db_connection()
    cursor = conn.cursor()

    # Fetch the playlist by its ID
    cursor.execute("SELECT PlaylistID, PlaylistName, ListenerID FROM Playlist WHERE PlaylistID = ?", (playlist_id,))
    playlist = cursor.fetchone()

    # Fetch all listeners for the dropdown list
    cursor.execute("SELECT ListenerID, ListenerName FROM Listener")
    listeners = cursor.fetchall()

    if request.method == 'POST':
        playlist_name = request.form['playlist_name']
        listener_id = request.form['listener_id']

        # Update the playlist in the database
        cursor.execute("UPDATE Playlist SET PlaylistName = ?, ListenerID = ? WHERE PlaylistID = ?", 
                       (playlist_name, listener_id, playlist_id))
        conn.commit()
        conn.close()

        flash("Playlist updated successfully!")
        return redirect(url_for('index'))  # Redirect to the index page or another page as needed

    conn.close()
    return render_template('update_playlist.html', playlist=playlist, listeners=listeners)


@app.route('/update_play_history/<int:listener_id>/<int:song_id>/<string:play_date>', methods=['GET', 'POST'])
def update_play_history(listener_id, song_id, play_date):
    conn = get_db_connection()
    cursor = conn.cursor()

    # Fetch the play history by listener_id, song_id, and play_date
    cursor.execute("SELECT ListenerID, SongID, PlayDate FROM PlayHistory WHERE ListenerID = ? AND SongID = ? AND PlayDate = ?", 
                   (listener_id, song_id, play_date))
    play_history = cursor.fetchone()

    # Fetch all listeners and songs for the dropdown lists
    cursor.execute("SELECT ListenerID, ListenerName FROM Listener")
    listeners = cursor.fetchall()

    cursor.execute("SELECT SongID, SongName FROM Song")
    songs = cursor.fetchall()

    if request.method == 'POST':
        new_listener_id = request.form['listener_id']
        new_song_id = request.form['song_id']
        new_play_date = request.form['play_date']

        # Update the play history in the database
        cursor.execute("UPDATE PlayHistory SET ListenerID = ?, SongID = ?, PlayDate = ? WHERE ListenerID = ? AND SongID = ? AND PlayDate = ?", 
                       (new_listener_id, new_song_id, new_play_date, listener_id, song_id, play_date))
        conn.commit()
        conn.close()

        flash("Play history updated successfully!")
        return redirect(url_for('index'))  # Redirect to the index page or another page as needed

    conn.close()
    return render_template('update_play_history.html', play_history=play_history, listeners=listeners, songs=songs)



@app.route('/update_playlist_song/<int:playlist_id>/<int:song_id>', methods=['GET', 'POST'])
def update_playlist_song(playlist_id, song_id):
    conn = get_db_connection()
    cursor = conn.cursor()

    # Fetch the playlist song by playlist_id and song_id
    cursor.execute("SELECT PlaylistID, SongID FROM PlaylistSong WHERE PlaylistID = ? AND SongID = ?", 
                   (playlist_id, song_id))
    playlist_song = cursor.fetchone()

    # Fetch all playlists and songs for the dropdown lists
    cursor.execute("SELECT PlaylistID, PlaylistName FROM Playlist")
    playlists = cursor.fetchall()

    cursor.execute("SELECT SongID, SongName FROM Song")
    songs = cursor.fetchall()

    if request.method == 'POST':
        new_playlist_id = request.form['playlist_id']
        new_song_id = request.form['song_id']

        # Update the playlist song in the database
        cursor.execute("UPDATE PlaylistSong SET PlaylistID = ?, SongID = ? WHERE PlaylistID = ? AND SongID = ?", 
                       (new_playlist_id, new_song_id, playlist_id, song_id))
        conn.commit()
        conn.close()

        flash("Playlist song updated successfully!")
        return redirect(url_for('index'))  # Redirect to the index page or another page as needed

    conn.close()
    return render_template('update_playlist_song.html', playlist_song=playlist_song, playlists=playlists, songs=songs)

    return render_template('update_playlist_song.html', playlist_song=playlist_song, playlists=playlists, songs=songs)



if __name__ == "__main__":
    app.run(debug=True)
