#ifndef essential_hpp
#define essential_hpp

#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<filesystem>
#include <random>
#include <stdexcept>
using namespace std;

class EssentialFunction {
    public:
        vector<string> split(const string &s, char delimiter);
        vector<vector<string> > read_csv(string file_directory);
        SDL_Texture* loadTexture (const string& path, SDL_Renderer* renderer);
        vector<SDL_Texture*> read_image_folder(string& path, SDL_Renderer* renderer);

        template <typename AUTO_TYPE> 
        AUTO_TYPE choice(const vector<AUTO_TYPE>& vec) {
            if (vec.empty()) {
                throw invalid_argument("Cannot select an element from an empty vector.");
            }
            random_device rd; 
            mt19937 gen(rd()); 
            uniform_int_distribution<> distrib(0, vec.size() - 1);
            return vec[distrib(gen)];
        }
        int randint(int min_number, int max_number);

    private:
};

template<typename T, unsigned D>
struct MultiDimVector {
    using NestedVector = typename MultiDimVector<T, D-1>::type;
    using type = vector<NestedVector>;
    type data;

    NestedVector& operator[](size_t i) {
        return data[i];
    }

    const NestedVector& operator[](size_t i) const {
        return data[i];
    }

    void resize(const vector<int>& sizes) {
        if (sizes.size() != D) {
            throw invalid_argument("Invalid Size");
        }
        data.resize(sizes[0]);
        for (auto& subvec : data) {
            MultiDimVector<T, D-1> temp;
            temp.data = subvec; 
            temp.resize(vector<int>(sizes.begin() + 1, sizes.end()));
            subvec = temp.data; 
        }
    }

    size_t size() const {
        return data.size();
    }

    auto begin() { return data.begin(); }
    auto end() { return data.end(); }
    auto begin() const { return data.begin(); }
    auto end() const { return data.end(); }
};

template<typename T>
struct MultiDimVector<T, 1> {
    using type = vector<T>;
    type data;

    T& operator[](size_t i) {
        return data[i];
    }

    const T& operator[](size_t i) const {
        return data[i];
    }

    void resize(const vector<int>& sizes) {
        if (sizes.size() != 1) {
            throw invalid_argument("Invalid Size");
        }
        data.resize(sizes[0]);
    }

    size_t size() const {
        return data.size();
    }

    auto begin() { return data.begin(); }
    auto end() { return data.end(); }
    auto begin() const { return data.begin(); }
    auto end() const { return data.end(); }
};

#endif