#include <iostream>
#include <string>
// #include "Block.cpp"
#include "hash.h"
#include <vector>


using namespace std;

void print_hex(const char *label, const uint8_t *v, size_t len) {
    size_t i;

    printf("%s: ", label);
    for (i = 0; i < len; ++i) {
        printf("%02x", v[i]);
    }
    printf("\n");
}

class Block {
    public:
        Block(string prevHas, vector<string> trans  );
        string getPreviousHash(void);
        string getHash(void);
        vector<string> getTransaction(void);

        void toString(void);
    private:
        string previousHash;
        string blockHash;
        vector<string> transactions;
        string getMerkleRoot(const vector<string> &merkle);
};
Block::Block( string prevHash, vector<string> trans ) {
    printf("Initializing Block....\n\n");
    this -> previousHash = prevHash;
    this -> transactions = trans;
    string header = getMerkleRoot(trans) + previousHash;
    this -> blockHash = sha256(header);
        
}
string Block::getPreviousHash(void) {
    return this -> previousHash;
}
string Block::getHash(void) {
    return this -> blockHash;
}
vector<string> Block::getTransaction(void){
    return this -> transactions;
}
void Block::toString(void) {
    cout << "Block hash: " << this -> blockHash << "prevHash: " << this -> previousHash;
}

string Block::getMerkleRoot(const vector<string> &merkle) {
    printf("Finding Merkle Root.... \n");
    if (merkle.empty())
        return "";
    else if (merkle.size() == 1){
        return sha256(merkle[0]);
    }

    vector<string> new_merkle = merkle;

    while (new_merkle.size() > 1) {
        if ( new_merkle.size() % 2 == 1 )
            new_merkle.push_back(merkle.back());

        vector<string> result;
            
        for (int i=0; i < new_merkle.size(); i += 2){
            string var1 = sha256(new_merkle[i]);
            string var2 = sha256(new_merkle[i+1]);
            string hash = sha256(var1+var2);
            printf("---hash(hash(%s), hash(%s)) => %s\n",new_merkle[0].c_str(),new_merkle[1].c_str(),hash.c_str());
            result.push_back(hash);
        }
        new_merkle = result;
    }
    printf("\n");
    return new_merkle[0];

}

// string Block::getTransactions(void)  {
//     return Block::transactions;
// }

int main() {
    string s = "Hello Bitcoin!";    

    // uint8_t digest[32];
    string digest = sha256(s);

    vector<string> v;
    string str = "hello";
    string third = "third";
    string fourth = "fourth";
    v.push_back(s);
    v.push_back(str);
    v.push_back(string("init string"));
    v.push_back(string("final string"));

    string initHash = "00000000000";
    Block genesis = Block(initHash,v);
    cout << genesis.getHash();
    Block b1 = Block(genesis.getHash(),v);
    cout << b1.getHash();
    printf("\n");
    return 0;
} 

