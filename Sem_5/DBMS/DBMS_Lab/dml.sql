-- Insert data into Listener table
INSERT INTO Listener (ListenerID, ListenerName, Email)
VALUES
(1, 'Alice', 'alice@example.com'),
(2, 'Bob', 'bob@example.com'),
(3, 'Charlie', 'charlie@example.com');

-- Insert data into Artist table
INSERT INTO Artist (ArtistID, ArtistName)
VALUES
(1, 'Taylor Swift'),
(2, 'Ed Sheeran'),
(3, 'Adele');

-- Insert data into Song table
INSERT INTO Song (SongID, SongName, ArtistID)
VALUES
(1, 'Love Story', 1),
(2, 'Shape of You', 2),
(3, 'Someone Like You', 3),
(4, 'Bad Blood', 1),
(5, 'Perfect', 2);

-- Insert data into Playlist table
INSERT INTO Playlist (PlaylistID, PlaylistName, ListenerID)
VALUES
(1, 'Chill Vibes', 1),
(2, 'Workout Hits', 2),
(3, 'Romantic Songs', 3);

-- Insert data into PlayHistory table
INSERT INTO PlayHistory (ListenerID, SongID, PlayDate)
VALUES
(1, 1, '2024-01-01'),
(1, 2, '2024-01-02'),
(2, 3, '2024-01-03'),
(3, 4, '2024-01-04'),
(3, 5, '2024-01-05');

-- Insert data into PlaylistSong table
INSERT INTO PlaylistSong (PlaylistID, SongID)
VALUES
(1, 1),
(1, 3),
(2, 2),
(2, 4),
(3, 1),
(3, 5);
