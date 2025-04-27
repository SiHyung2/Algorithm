#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

struct huffmanNode {
    char a;
    int fre;
    huffmanNode* left;
    huffmanNode* right;
};

struct cmp {
    bool operator()(huffmanNode* a, huffmanNode* b) {
        return a->fre > b->fre;
    }
};

class HuffmanTree {
public:
    // [4] ���α׷� ���� ����
    //     +  main()���� return�ɶ� ȣ��Ǵ� �޼ҵ��̴�
    //     + �Ҹ���: ��ü�� ���� ����� �� �ڵ� ȣ��Ǿ� Ʈ�� �޸� ����
    ~HuffmanTree() {
        releaseTree(root);
        root = nullptr;
        while (!pq.empty()) pq.pop();
    }

private: // + ���� ���� ������: �� �Ʒ� ������� Ŭ���� �ܺο��� ���� ���� �Ұ�
    huffmanNode* root = nullptr;
    unordered_map<char, int> ascii;
    unordered_map<char, string> code;
    // + �켱���� ť: �󵵰� ���� ��带 ���� ������ ���� ��� (cmp ���� ���)
    //    + ���� ����
    //       1. priority_queue<����ü��*, vector<����ü��*>, cmp>
    //       2. cmp���� �����ϴ� �޼ҵ带 �����ε��Ѵ�
    //       3. ��Ʈ�� �ּҰ��� �켱���� ť ����
    //           3-1. �ֳ��ϸ� cmp���� ù��°�� fre��(a->fre)�� �ι�°�� fre��(b->fre)���� Ŭ�� TRUE�� ��ȯ�ϱ⿡ ���������ӿ� ����
    //       4. ���������̹Ƿ� fre ���� ���� ���� ��Ұ� top()�� ��ġ�� ���� ���� ��������.
    //    + �޼ҵ�
    //       + push() : �켱���� ť�� ���Ҹ� �߰��Ѵ�
    //       + pop() : �켱���� ť���� top�� ���Ҹ� �����Ѵ�
    //       + top() : �켱���� ť���� ���� ���� �켱���� ���Ҹ� ��ȯ�Ѵ�
    
    priority_queue<huffmanNode*, vector<huffmanNode*>, cmp> pq;
    string text;

public:
    // [2] ��������� �ڵ�������� �� ���� ����
        // [2]-1: ifstream file("sample.txt"); �� ���� ����
        // [2]-2: while (getline(file, text)) {...}
            //    [2]-2-a: �� �� �о� text�� ����
            //    [2]-2-b : for (char ch : text) �� �� ���ڿ� ���� ++ascii[ch](�� ����)
        // [2]-3: for (const auto& iter : ascii)
            //    [2]-3-a : new huffmanNode{ �� } �� ���ڡ��� ��� ����
            //    [2]-3-b : pq.push(node) �� �켱���� ť�� ����
        // [2]-4: MakeTree(): ������ Ʈ�� ����
            // [2]-4-a : rounds = pq.size() - 1
                // + left = ���� ���� ��
                // + right = �� ��°�� ���� ��
                // + parent = ��ģ ���
            // [2]-4-b : �ݺ��� i=0��rounds-1
            // [2]-4-c : root = pq.top(); (���� ��Ʈ ����)
        // [2]-5: 
            // [2]-5-a : ��� ȣ��� ����(+'0')/������(+'1') ��������
            // [2]-5-b : ���� ��� ���� �� code[char] = bits ����

    void Start() {
        ifstream file("sample.txt");
        while (getline(file, text)) {
            for (char ch : text) {
                // + ���� �� ī��Ʈ
                ++ascii[ch];
            }
            ++ascii['\n'];
        }



        cout << endl << "=============================" << endl << " (1) ���� �� ī��Ʈ �� ���" << endl << "=============================" << endl;
        for (auto& kv : ascii) {
            cout << kv.first << " : " << kv.second << endl;
        }

        for (const auto& iter : ascii) { // + ascii �� ��Ҹ� const ������ ��ȸ
            // + auto* node: auto�� Ÿ��(huffmanNode*)�� �߷�. auto�� ������ ���� �ڵ����� ��������!
            auto* node = new huffmanNode{ iter.first, iter.second, nullptr, nullptr };
            pq.push(node);
        }

        // ������ Ʈ�� ����
        MakeTree();

        // Ʈ�� ��ȸ�Ͽ� �ڵ� �� ����
        FindTree(root, "");
    }

    // �ڵ� ���
    // [3] T.showCode(); ȣ��
        // [3]-1: for (auto& kv : code) ��ȸ
        // [3]-2: cout << kv.first << " : " << kv.second ���
    void showCode() {
        for (auto& kv : code) {
            cout << kv.first << " : " << kv.second << "\n";
        }
    }
    
    // [4] �ϼ��� ������ �ڵ带 ����Ͽ� ���� ���ڵ�
    // [4]-1: sample.txt���� ���� �ϳ��� �о� code[char]�� sample.enc�� ���
    void encodeFile(const string& inFile, const string& outFile) {
        ifstream fin(inFile);
        ofstream fout(outFile);
        cout << "3-���. sample.txt -> sample.enc ���ڵ� �Ϸ�" << endl << endl;
        char ch;
        while (fin.get(ch)) {
            fout << code[ch];
        }
        fin.close();
        fout.close();
    }

    // [5] ���ڵ��� ����(sample.enc)�� �������� ���ڵ�
    // [5]-1: sample.enc���� ��Ʈ �ϳ��� �о� tree Ž���Ͽ� ���� ����, sample.dec�� ���
    void decodeFile(const string& inFile, const string& outFile) {
        ifstream fin(inFile);
        ofstream fout(outFile);
        cout << "4-���. sample.enc -> sample.dec ���ڵ� �Ϸ�\n";
        huffmanNode* node = root;
        char bit;
        while (fin.get(bit)) {
            if (bit == '0') node = node->left;
            else node = node->right;
            if (node->left == nullptr && node->right == nullptr) {
                fout.put(node->a);
                node = root;
            }
        }
        fin.close();
        fout.close();
    }

    // [6] ���ڵ�� ���ϰ� ���� ���� ��
    void verifyFile(const string& origFile, const string& decFile) {
        ifstream a(origFile);
        ifstream b(decFile);
        cout << "5. sample.dec�� sample.txt ��ġ ����: ";
        string lineA, lineB;
        bool match = true;
        while (true) {
            bool eA = bool(getline(a, lineA));
            bool eB = bool(getline(b, lineB));
            if (!eA && !eB) break;
            if (lineA != lineB) { match = false; break; }
        }
        cout << (match ? "Yes\n" : "No\n");
        a.close(); b.close();
    }

    // [7] ���� ��/�� ��Ʈ �� �� ����� ���
    void compressionStats(const string& origFile, const string& encFile) {
        ifstream o(origFile, ios::ate | ios::binary);
        ifstream e(encFile, ios::ate | ios::binary);
        long long origBits = o.tellg() * 8;
        long long encBits = e.tellg();
        double ratio = (1.0 - double(encBits) / origBits) * 100.0;
        cout << "6. ���� ���:" << endl;
        cout << "   ���� ��Ʈ ��: " << origBits << "\n";
        cout << "   ���� �� ��Ʈ ��: " << encBits << "\n";
        cout << "   �����: " << ratio << "%\n";
        o.close(); e.close();
    }

private:
    // Ʈ�� ����: �� ���� �� ��带 ���� ���ο� ���� ��� ����
    void MakeTree() {
        int rounds = pq.size() - 1;
        for (int i = 0; i < rounds; ++i) {
            auto* left = pq.top(); pq.pop();    // 1) left���� ���� ���� �� ��� �ֱ�. �״���, pq���� �׳�� ����
            auto* right = pq.top(); pq.pop();    // 2) right���� �� ��° ���� �� ��� �ֱ�. �״��� pd���� �׳�� ����
            auto* parent = new huffmanNode{ 0, left->fre + right->fre, left, right };
            pq.push(parent);                      // 3) ��ģ ��� �ٽ� ����
        }
        root = pq.top();                          // + ��Ʈ ��� ����
    }

    // + [4] Ʈ�� ��ȸ: �������� ������ ��Ʈ ���ڿ��� �ڵ�� ����
    void FindTree(huffmanNode* node, string bits) {
        if (!node) return;
        FindTree(node->left, bits + '0');
        FindTree(node->right, bits + '1');
        if (node->a != 0) {
            code[node->a] = bits;  // + ���� ���: ���ں� ������ �ڵ� ����
        }
    }

    // + �޸� ����: ���� ��ȸ�� ����
    //     + main()�� return�ɶ� ����Ǵ� �Լ��ȿ� ����ִ� �޼ҵ��̴�
    void releaseTree(huffmanNode* node) {
        if (!node) return;
        releaseTree(node->left);
        releaseTree(node->right);
        delete node; // + new�� �Ҵ�� �޸� ����: ��ü�� �Ҹ��� ȣ�� �� �޸� ��ȯ
    }
};

int main() {
    // [1] HuffmanTree ��ü ����: ������ �غ�
    //  + T ��ü�� �޸� ���� ������� (�⺻ ������ ����, ��� �������� ���� �� �ʱⰪ(nullptr, �� �����̳�)���� ����)

    HuffmanTree T;

    // [2] Start ȣ��: ���� �б� �� �� ���� �� Ʈ�� ���� �� �ڵ� ����
    T.Start();

    // [3] ������ �ڵ� ���
    cout << endl << "=============================" << endl << " (2) 1���� ������ ���� ����Ͽ� huffman code�� �ϼ��Ͻÿ�." << endl << "=============================" << endl;
    T.showCode();

    // [4] ���ڵ� ����
    cout << endl << "=============================" << endl << " (3) �ϼ��� huffman code�� ����Ͽ� sample.txt ������ encode �Ͻÿ�. (sample.enc)" << endl << "=============================" << endl;
    T.encodeFile("sample.txt", "sample.enc");

    // [5] ���ڵ� ����
    cout << endl << "=============================" << endl << " (4) 3������ enc�� ������ ���� sample ���Ϸ� decode �Ͻÿ�. (sample.dec)" << endl << "=============================" << endl;
    T.decodeFile("sample.enc", "sample.dec");

    // [6] ���ڵ�� ���ϰ� ���� ���� ��
    cout << endl << "=============================" << endl << " (5) ���ڵ�� sample.dec ���ϰ� ������ sample.txt ������ ��ġ�ϴ��� Ȯ���Ͻÿ�." << endl << "=============================" << endl;
    T.verifyFile("sample.txt", "sample.dec");

    // [7] ���� ��/�� ��Ʈ �� �� ����� ���
    cout << endl << "=============================" << endl << " (6) �������� ���� ��Ʈ���� ����Ͽ� �����(%)�� ����Ͻÿ�." << endl << "=============================" << endl;
    T.compressionStats("sample.txt", "sample.enc");

    // [8] ���α׷� ���� ���� �� ���α׷� ����, ���� T �Ҹ���(~HuffmanTree()) �ڵ� ȣ��
        // [8]-1: releaseTree(root) �� Ʈ�� ��� �޸� ���� ����
        // [8]-2: while (!pq.empty()) pq.pop(); �� ť ����
    return 0;
}