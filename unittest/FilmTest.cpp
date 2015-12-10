#include <gtest/gtest.h>
#include "Film.h"

TEST(FilmTest, CommitRightPlace) {

    Film film = Film(2, 1);
    
    Color color = Color(1, 0.2, 0.5); // RGB
    
    Sample sample = Sample(0.5, 0.5);
    
    film.commit(sample, color);
    
    // BGR order
    
    EXPECT_EQ(film.getPixel(0), 127);
    EXPECT_EQ(film.getPixel(1), 51);
    EXPECT_EQ(film.getPixel(2), 255);
    
    Color color2 = Color(0.1, 0.2, 0.3);
    Sample sample2 = Sample(1.5, 0.5);
    
    film.commit(sample2, color2);
    
    EXPECT_EQ(film.getPixel(3), 76);
    EXPECT_EQ(film.getPixel(4), 51);
    EXPECT_EQ(film.getPixel(5), 25);

}
