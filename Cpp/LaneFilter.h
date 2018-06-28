//
// Created by Jack Xu on 2018-06-28.
//

#ifndef CPP_LANEFILTER_H
#define CPP_LANEFILTER_H


class LaneFilter {
public:
    LaneFilter(); //Custom Constructor
    ~LaneFilter(); //Destructor, must release all objects/pointers

    void applyFilter();

private:
    void hsvFilter();
    void grayFilter();
    void CannyGradientFilter();

    /* Example : this is an example code, please follow this guidline
     * @param input_ : some input
     * @param out_: some output (explain the param)
     */
    void Example(int input_, int &out_);

};


#endif //CPP_LANEFILTER_H
