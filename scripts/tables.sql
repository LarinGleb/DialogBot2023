
CREATE TABLE events (
  ID serial PRIMARY KEY NOT NULL,
  name TEXT NOT NULL,
  description TEXT NOT NULL,
  date DATE NOT NULL
);

CREATE TABLE reviews (
  ID serial PRIMARY KEY NOT NULL,
  event_id INT NOT NULL,
  user_id BIGINT NOT NULL,
  date DATE NOT NULL,
  mark_event INT NOT NULL,
  change TEXT NOT NULL,
  good TEXT NOT NULL,
  next_year TEXT NOT NULL
);
