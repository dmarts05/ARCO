#include "recount.h"

/**
 * @brief recount::recount empty constructor
 */
recount::recount()
{
    this->code = -1;
}

recount::recount(vector<string> data)
{
    // Data given by the csv file
    this->code = stoi(data[0]);
    this->municipal = data[1];
    this->zone = stoi(data[2]);
    this->section = stoi(data[3]);
    this->name = data[4][0];
    this->census = stoi(data[5]);
    this->abstentions = stoi(data[6]);
    this->v_cast = stoi(data[7]);
    this->v_invalid = stoi(data[8]);
    this->v_valid = stoi(data[9]);
    this->v_white = stoi(data[10]);

    // Data to calculate
    this->p_participation = 0;
    this->p_abstention = 0;
}

// GETTERS
int recount::get_code()
{
    return this->code;
}

int recount::get_v_cast()
{
    return this->v_cast;
}

int recount::get_abstentions()
{
    return this->abstentions;
}

int recount::get_census()
{
    return this->census;
}

float recount::get_p_participation()
{
    return this->p_participation;
}

float recount::get_p_abstention()
{
    return this->p_abstention;
}

// SETTERS
void recount::set_p_participation(float p_participation)
{
    this->p_participation = p_participation;
}

void recount::set_p_abstention(float p_abstention)
{
    this->p_abstention = p_abstention;
}

// PRINT
void recount::print()
{
    cout << "Code: " << this->code << endl;
    cout << "Municipal: " << this->municipal << endl;
    cout << "Zone: " << this->zone << endl;
    cout << "Section: " << this->section << endl;
    cout << "Name: " << this->name << endl;
    cout << "Census: " << this->census << endl;
    cout << "Abstentions: " << this->abstentions << endl;
    cout << "Voted: " << this->v_cast << endl;
    cout << "Invalid: " << this->v_invalid << endl;
    cout << "Valid: " << this->v_valid << endl;
    cout << "White: " << this->v_white << endl;
    cout << "Participation: " << this->p_participation << endl;
    cout << "Abstention: " << this->p_abstention << endl;
    cout << endl;
}