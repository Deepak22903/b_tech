-- Create Listener Table
CREATE TABLE Listener (
    ListenerID INT PRIMARY KEY AUTO_INCREMENT,
    ListenerName VARCHAR(100) NOT NULL,
    Email VARCHAR(100) NOT NULL
);

-- Create Artist Table
CREATE TABLE Artist (
    ArtistID INT PRIMARY KEY,
    ArtistName VARCHAR(100) NOT NULL
);

-- Create Song Table
CREATE TABLE Song (
    SongID INT PRIMARY KEY,
    SongName VARCHAR(100) NOT NULL,
    ArtistID INT,
    FOREIGN KEY (ArtistID) REFERENCES Artist(ArtistID)
        ON DELETE CASCADE ON UPDATE CASCADE
);

-- Create Playlist Table
CREATE TABLE Playlist (
    PlaylistID INT PRIMARY KEY,
    PlaylistName VARCHAR(100) NOT NULL,
    ListenerID INT,
    FOREIGN KEY (ListenerID) REFERENCES Listener(ListenerID)
        ON DELETE CASCADE ON UPDATE CASCADE
);

-- Create PlayHistory Table (Composite primary key)
CREATE TABLE PlayHistory (
    ListenerID INT,
    SongID INT,
    PlayDate DATE,
    PRIMARY KEY (ListenerID, SongID, PlayDate),
    FOREIGN KEY (ListenerID) REFERENCES Listener(ListenerID)
        ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (SongID) REFERENCES Song(SongID)
        ON DELETE CASCADE ON UPDATE CASCADE
);

-- Create PlaylistSong Table (Composite primary key)
CREATE TABLE PlaylistSong (
    PlaylistID INT,
    SongID INT,
    PRIMARY KEY (PlaylistID, SongID),
    FOREIGN KEY (PlaylistID) REFERENCES Playlist(PlaylistID)
        ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (SongID) REFERENCES Song(SongID)
        ON DELETE CASCADE ON UPDATE CASCADE
);
