#include <bits/stdc++.h>
using namespace std;
struct Item{
    char Item_Name[15];
    char Item_Category[15];
    int Item_quantity;
};
struct PrimaryIndex{
    char Item_Name[15];
    int RRN;
    bool operator<(const PrimaryIndex &r) const { // for the sort function
        return strcmp(Item_Name, r.Item_Name) < 0;
    }
};
struct SecondryIndex {
    char Item_Name[15];
    char Item_Category[15];
    bool operator<(const SecondryIndex &r) const { // for the sort function
        if (strcmp(Item_Category, r.Item_Category) == 0)//If two categories are same
            return strcmp(Item_Name, r.Item_Name) < 0;
        return strcmp(Item_Category, r.Item_Category) < 0;//Else return 0 or 1 if the first cat < the second cat
    }
};
void toLower(char str[15]){
    for (int i=0; i<strlen(str); i++)
        tolower(str[i]);
}
void WritePrimIndex(PrimaryIndex PrmIndxArray[],int numRec, fstream&outfile) {
    for (int i = 0; i < numRec; i++)
        outfile.write((char*) &PrmIndxArray[i], sizeof PrmIndxArray[i]);
}
void WriteSecndIndex(SecondryIndex ScndIndxArray[], int numRec, fstream&outfile) {
    for (int i = 0; i < numRec; i++)
        outfile.write((char*) &ScndIndxArray[i], sizeof ScndIndxArray[i]);
}
int getNumRec(fstream& inFile){//For loop used to return the current number of records
    //when the program is initially run
    int c=0;
    Item item;
    if(!inFile){
        return c;
    }
    else{
        while(!inFile.eof()){
            c++;
            inFile.read((char*) &item, sizeof item);
        }
        return c;
    }


}
void ReadPrimIndex(PrimaryIndex PrmIndxArray[],int numRec, fstream& inFile) {
    for (int i = 0; i < numRec; i++)
        inFile.read((char*) &PrmIndxArray[i], sizeof PrmIndxArray[i]);
}
void ReadSecndIndex(SecondryIndex ScndIndxArray[], int numRec, fstream& inFile) {
    for (int i = 0; i < numRec; i++)
        inFile.read((char *) &ScndIndxArray[i], sizeof ScndIndxArray[i]);
}
int addNewItem(PrimaryIndex PrmIndxArray[],SecondryIndex ScndIndxArray[],int x){
    fstream file("ShoopingList.txt",ios::app);
    fstream primFile("PrimaryIndex.txt",ios::app);
    fstream ScndIndex("SecondryIndex.txt",ios::app);
    cout << "Enter Number Of Input Records:";
    int numRec;
    cin>>numRec;
    Item *items = new Item[numRec];
    for (int i = x; i < numRec+x; i++) {
        Item item;
        cin.ignore();
        cout << "Enter the item's information: \n";
        cout << "Item name: ";
        cin.getline(item.Item_Name, 15);
        cout << "Item category: ";
        cin.getline(item.Item_Category, 15);
        cout << "Item quantity: ";
        cin >> item.Item_quantity;
        toLower(item.Item_Name);
        toLower(item.Item_Category);
        items[i]=item;
        PrmIndxArray[i].RRN = i;
        strcpy(PrmIndxArray[i].Item_Name, item.Item_Name);
        strcpy(ScndIndxArray[i].Item_Category, item.Item_Category);
        //insert in the set
        strcpy(ScndIndxArray[i].Item_Name, item.Item_Name);
        file.write((char *) &(items[i]), sizeof(items[i]));

    }
    sort(PrmIndxArray, PrmIndxArray + numRec+x);
    sort(ScndIndxArray, ScndIndxArray + numRec+x);
    WritePrimIndex(PrmIndxArray,numRec+x, primFile);
    WriteSecndIndex(ScndIndxArray, numRec+x, ScndIndex);
    file.close();
    primFile.close();
    ScndIndex.close();
    return numRec;
}


void readNames(int numRec){
    fstream file("ShoopingList.txt",ios::in);
    for(int i=0;i<numRec;++i){
        Item item;
        file.read((char *)&item,sizeof (item));
        cout<<"Name: "<<item.Item_Name<<endl;
    }
    file.close();
}
void readCategories(int numRec){
    fstream file("ShoopingList.txt",ios::in);

    for(int i=0;i<numRec;++i){
        Item item;
        file.read((char *)&item,sizeof (item));
        cout<<"Category: "<<item.Item_Category<<endl;
    }
    file.close();
}
int GetItemNameRRN(PrimaryIndex PrmIndxArray[], int numRec, string name) {
    int RRN = -1;
    int low = 0, mid, high = numRec - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if (name < PrmIndxArray[mid].Item_Name)
            high = mid - 1;
        else if (name > PrmIndxArray[mid].Item_Name)
            low = mid + 1;
        else {
            RRN = PrmIndxArray[mid].RRN;
            break;
        }
    }
    return RRN;
}
int GetPrimIndex(PrimaryIndex PrmIndxArray[], int numRec, string name) {
    int RRN = -1;
    int low = 0, mid, high = numRec - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if (name < PrmIndxArray[mid].Item_Name)
            high = mid - 1;
        else if (name > PrmIndxArray[mid].Item_Name)
            low = mid + 1;
        else {
            break;
        }
    }
    return mid;
}
int GetScIndex(SecondryIndex ScndIndxArray[], int numRec, string name) {
    int RRN = -1;
    int low = 0, mid, high = numRec - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if (name < ScndIndxArray[mid].Item_Name)
            high = mid - 1;
        else if (name > ScndIndxArray[mid].Item_Name)
            low = mid + 1;
        else {
            break;
        }
    }
    return mid;
}
void GetItemQuantity(int RRN) {
    fstream file("ShoopingList.txt",ios::in);
    Item item;
    file.seekg(RRN * sizeof (item), ios::beg);
    file.read((char*) &item, sizeof item);
    cout<<"The quantity of this item is: "<<item.Item_quantity<<endl;
}
void printQuantityInSpecificCategory(char itemCat[15],int numRec){
    fstream file("ShoopingList.txt",ios::in);
    for(int i=0;i<numRec;++i){
        Item item;
        file.read((char*) &item, sizeof item);
        if(strcmp(itemCat, item.Item_Category) == 0){
            cout<<"The quantity of "<<item.Item_Name<<" is: "<<item.Item_quantity<<endl;
        }
    }
}
void printItemInSpecificCategory(char itemCat[15],int numRec){
    fstream file("ShoopingList.txt",ios::in);
    for(int i=0;i<numRec;++i){
        Item item;
        file.read((char*) &item, sizeof item);
        if(strcmp(itemCat, item.Item_Category) == 0){
            cout<<"Item name: "<<item.Item_Name<<endl;
            cout<<"Item category: "<<item.Item_Category<<endl;
            cout<<"Item quantity: "<<item.Item_quantity<<endl;
        }
    }
}

int main() {
    PrimaryIndex *PrmIndxArray = new PrimaryIndex[10];
    SecondryIndex *ScndIndxArray = new SecondryIndex[10];
    fstream file("ShoopingList.txt",ios::in);
    int numRec=getNumRec(file);
    fstream primFile("PrimaryIndex.txt",ios::in);//To read what is in the primary index file in the current moment
    fstream ScndIndex("SecondryIndex.txt",ios::in);//To read what is in the secondary index file in the current moment
    ReadPrimIndex(PrmIndxArray,numRec,primFile);
    ReadSecndIndex(ScndIndxArray,numRec,ScndIndex);
    //Fill the set with shoppingList
    file.close();
    primFile.close();
    ScndIndex.close();
    cout<<"Welcome to our shop \n";
    while(true){

        cout<<"******************************************************************************* \n";
        cout<<"1- Add new item to the shopping list \n";//Done
        cout<<"2- Print all items names in the shopping list \n";//Done
        cout<<"3- Print all items categories in the shopping list \n";//----->
        cout<<"4- Print quantity of an item in the list with specific name or category \n";//Done
        cout<<"5- Count the number of items in the shopping list \n";//Done
        cout<<"6- Count the number of categories in the shopping list \n";//------>
        cout<<"7- Search for an item in the shopping list by Name, or Category  \n";//Done
        cout<<"8- Update item information  \n";//Done
        cout<<"9- Exit  \n";
        char choice;
        cout<<"Enter your choice: ";cin>>choice;
        if(choice=='1'){//Add new item to the shopping list

            numRec+=addNewItem(PrmIndxArray,ScndIndxArray,numRec);

        }
            //End of choice 1
        else if(choice=='2'){//Print all items names in the shopping list
            readNames(numRec);
        }
            //End of choice 2
        else if(choice=='3'){//Print all items categories in the shopping list
            readCategories(numRec);
        }
            //End of choice 3
        else if(choice=='4'){//Print quantity of an item in the list with specific name or category
            cout<<"1- By name \n";
            cout<<"2- By category \n";
            char x;
            cout<<"Enter your choice: ";cin>>x;
            cin.ignore();
            if(x=='1'){//By name
                char itemName[15];
                cout << "Item name: ";
                cin.getline(itemName, 15);
                int rrn=GetItemNameRRN(PrmIndxArray,numRec,itemName);
                if(rrn==-1){
                    cout<<"This name is not found in the list \n";
                }
                else{
                    GetItemQuantity(rrn);
                }
            }
            else if(x=='2'){//By category
                char itemCat[15];
                cout << "Item category: ";
                cin.getline(itemCat, 15);
                printQuantityInSpecificCategory(itemCat,numRec);
            }
            else{
                cout<<"Invalid choice \n";
            }

        }
            //End of choice 4
        else if(choice=='5'){//Count the number of items in the shopping list
            cout<<"number of items in the shopping list is: "<<numRec<<endl;
        }
            //End of choice 5
        else if(choice=='6'){//Count the number of categories in the shopping list
            bool flag1 = false ;
            vector <string> catogry;
            for (int i = 0; i < numRec; i++)
            {
                for (int j = i+1; j <= sizeof(ScndIndxArray)/sizeof(ScndIndxArray[0]); j++)
                {
                    if (ScndIndxArray[i].Item_Category == catogry[j])
                    {
                        flag1= true;
                    }
                }
                if (flag1 == false)
                {
                    catogry.push_back(ScndIndxArray[i].Item_Category);
                }

            }
            //           file.close();
            cout << "number of catogries : " << catogry.size() << endl;
        }
            //End of choice 6
        else if(choice=='7'){//Search for an item in the shopping list by Name, or Category
            cout<<"1- By name \n";
            cout<<"2- By category \n";
            char x;
            cout<<"Enter your choice: ";cin>>x;
            cin.ignore();
            if(x=='1'){//By name
                char itemName[15];
                cout << "Item name: ";
                cin.getline(itemName, 15);
                toLower(itemName);
                int rrn=GetItemNameRRN(PrmIndxArray,numRec,itemName);
                if(rrn==-1){
                    cout<<"This name is not found in the list \n";
                }
                else{
                    fstream file("ShoopingList.txt",ios::in);
                    Item item;
                    file.seekg(rrn * sizeof (item), ios::beg);
                    file.read((char*) &item, sizeof item);
                    cout<<"Item name: "<<item.Item_Name<<endl;
                    cout<<"Item category: "<<item.Item_Category<<endl;
                    cout<<"Item quantity: "<<item.Item_quantity<<endl;
                    file.close();
                }
            }
            else if(x=='2'){//By category
                char itemCat[15];
                cout << "Item category: ";
                cin.getline(itemCat, 15);
                toLower(itemCat);
                printItemInSpecificCategory(itemCat,numRec);

            }
            else{
                cout<<"Invalid choice \n";
            }

        }
            //End of choice 7
        else if(choice=='8'){//Update item information
            fstream primFile1("PrimaryIndex.txt",ios::in |ios::out);
            fstream ScndIndex2("SecondryIndex.txt",ios::in | ios::out);
            cin.ignore();
            char itemName1[15];
            cout << "Item name: ";
            cin.getline(itemName1, 15);
            int rrn = GetItemNameRRN(PrmIndxArray, numRec, itemName1);
            if (rrn == -1) {
                cout << "This name is not found in the list \n";
            }
            else {
                int choice2;
                bool flag = true;
                while (flag)
                {
                    cout << "1- change Item name\n 2- change Item quantity\n 3- change Item category\n";
                    cin >> choice2;
                    if (choice2 == 1)
                    {
                        fstream file("ShoopingList.txt", ios::in |ios::binary | ios::out);
                        Item item;
                        file.seekg(rrn * sizeof(item), ios::beg);
                        file.read((char*) &item, sizeof item);
                        cout << "Enter new Item name\n";
                        cin.ignore();
                        cin.getline(item.Item_Name, 15);
                        file.seekp(rrn * sizeof(item), ios::beg);
                        file.write((char*) &item, sizeof item);
                        flag = false;
                        file.close();
                        int indx=GetPrimIndex(PrmIndxArray,numRec,item.Item_Name);
                        strcpy(PrmIndxArray[indx].Item_Name,item.Item_Name);
                        sort(PrmIndxArray, PrmIndxArray + numRec);
                        WritePrimIndex(PrmIndxArray,numRec, primFile1);
                    }

                    else if (choice2 == 2)
                    {
                        fstream file("ShoopingList.txt", ios::in |ios::binary | ios::out );
                        Item item;
                        file.seekg(rrn * sizeof(item), ios::beg);
                        file.read((char*) &item, sizeof item);
                        cout << "Enter new Item quantity\n";
                        cin>>item.Item_quantity;
                        file.seekp(rrn * sizeof(item), ios::beg);
                        file.write((char*) &item, sizeof item);
                        flag = false;
                        file.close();
                    }
                    else if (choice2 == 3)
                    {
                        fstream file("ShoopingList.txt", ios::in |ios::binary | ios::out);
                        Item item;
                        file.seekg(rrn * sizeof(item), ios::beg);
                        file.read((char*) &item, sizeof item);
                        cout << "Enter new Item category\n";
                        cin.ignore();
                        cin.getline(item.Item_Category, 15);
                        file.seekp(rrn * sizeof(item), ios::beg);
                        file.write((char*) &item, sizeof item);
                        flag = false;
                        file.close();
                        int indx=GetScIndex(ScndIndxArray,numRec,item.Item_Category);
                        strcpy(ScndIndxArray[indx].Item_Category,item.Item_Category);
                        sort(ScndIndxArray, ScndIndxArray + numRec);
                        WriteSecndIndex(ScndIndxArray, numRec, ScndIndex2);
                    }
                    else
                    {
                        cout << "Enter valid choice\n";
                    }
                }
            }
        }
            //End of choice 8
        else if(choice=='9'){//Exit
            cout<<"Thank you! \n";
            break;
        }
            //End of choice 9
        else {
            cout<<"Invalid choice please try again \n";
        }

    }
    return 0;
}
