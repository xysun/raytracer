#include <gtest/gtest.h>
#include "Film.h"

TEST(FilmTest, CommitRightPlace) {

    Film film = Film(3, 1);
    
    Color color = Color(1, 2, 3);
    
    Sample sample = Sample(0.5, 0.5);
    
    film.commit(sample, color);
    
    EXPECT_EQ(film.getPixel(0), 1);
    EXPECT_EQ(film.getPixel(1), 2);
    EXPECT_EQ(film.getPixel(2), 3);
    
    Color color2 = Color(4,5,6);
    Sample sample2 = Sample(1.5, 0.5);
    
    film.commit(sample2, color2);
    
    EXPECT_EQ(film.getPixel(3), 4);
    EXPECT_EQ(film.getPixel(4), 5);
    EXPECT_EQ(film.getPixel(5), 6);

}
