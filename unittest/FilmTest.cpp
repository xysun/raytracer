#include <gtest/gtest.h>
#include "Film.h"

TEST(FilmTest, CommitRightPlace) {

    Film film = Film(2, 1);
    
    Color color = Color(1, 2, 3); // RGB
    
    Sample sample = Sample(0.5, 0.5);
    
    film.commit(sample, color);
    
    // BGR order
    
    EXPECT_EQ(film.getPixel(0), 3);
    EXPECT_EQ(film.getPixel(1), 2);
    EXPECT_EQ(film.getPixel(2), 1);
    
    Color color2 = Color(4,5,6);
    Sample sample2 = Sample(1.5, 0.5);
    
    film.commit(sample2, color2);
    
    EXPECT_EQ(film.getPixel(3), 6);
    EXPECT_EQ(film.getPixel(4), 5);
    EXPECT_EQ(film.getPixel(5), 4);

}
