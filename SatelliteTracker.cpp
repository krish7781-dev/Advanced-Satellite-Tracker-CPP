#include <iostream>
#include <string>
using namespace std;


class SpaceObject{
    public:
    void rebootSystem(){
        cout<<"Rebooting Space Object Systems..."<<endl;

    }

    virtual void performChecking(){
        cout<<"Base: Basic Power Check Completed"<<endl;
    }
};

class Satellite: public virtual SpaceObject
{
    private:
      const float satelliteID;
      int orbitHeight;
      static int totalSatellites; //static variable to keep track of the total number of satellites created

    public:
     Satellite(int id, int h):satelliteID(id),orbitHeight(h) //constructor with initializer list to initialize the const variable satelliteID
     {
        totalSatellites++; //incrementing the totalSatellites variable every time a new satellite object is created
        
        cout<<"System: Satellite "<<satelliteID<<" is Online"<<endl;
        
    }


    void display(){
        cout<<"ID:"<<satelliteID<<"|Height:"<<orbitHeight<<"Km"<<endl;
    }

    static void ShowMissionStatus(){
        cout<<"----Mission Control:Total Satellites in Orbit----"<<totalSatellites<<endl; //accessing the static variable totalSatellites using the class name and scope resolution operator
        cout<<"----Mission Status: All Systems Operational----"<<endl;
    }

    void performChecking() override{
        cout<<"Satellite: Checking Orbital Trajectory and Communication Systems..."<<endl;
    }

    ~Satellite(){
        cout<<"System: Satellite "<<satelliteID<<" is de--orbitted"<<endl;
        totalSatellites--; //decrementing the totalSatellites variable every time a satellite object is destroyed
    }

};

int Satellite:: totalSatellites=0;  //initializing the static variable totalSatellites to 0
//This tells the compiler to reserve a single memory location for this variable that every satellite object will share




class researchLab:public virtual SpaceObject {
    private:
      int numscientists;
      int oxygenlevel;

      public:
         researchLab(int numscientists , int oxygenlevel){
            this->numscientists=numscientists;
            this->oxygenlevel=oxygenlevel;
            //cout<<"Research Lab is established with "<<numscientists<<" scientists and oxygen level is "<<oxygenlevel<<"%"<<endl;
            
        }

        void conductExperiment(){
            cout<<"Conducting experiment in the research lab with "<<numscientists<<" scientists and oxygen level is "<<oxygenlevel<<"%"<<endl;
        }
};

class SpaceStation:public Satellite , public researchLab,public virtual SpaceObject{
    public:
    SpaceStation(int id,int h, int numscientists, int oxygenlevel):Satellite(id,h),researchLab(numscientists, oxygenlevel){
        cout<<"Space Station Assembly Complete"<<endl;
    }
    
    void performChecking() override{
        cout<<"Checking Oxygen and Life Support";
    }

};

class SpySatellite : public Satellite{
    private:
      int CameraResolution;

      public:
        SpySatellite(int id , int h , int CameraResolution):Satellite(id,h){
            this->CameraResolution=CameraResolution;
            cout<<"Defence System: Imaging Sensors is Initialized:"<<CameraResolution<<"MP"<<endl;
        }
        
       void takephoto(){
        cout<<"Spy Satellite is taking a photo with "<<CameraResolution<<"MP resolution"<<endl;

 
       } 

};

void MissionController(SpaceObject *obj)
{
    cout<<"---Mission Control Interface---"<<endl;
    obj->performChecking(); //This will call the performChecking function of the derived class (Satellite or SpaceStation) because of dynamic dispatch, even though we are using a pointer of type SpaceObject, it will call the overridden function in the derived class at runtime.
    cout<<"--------End of Mission Control Report--------"<<endl;
}


int main(){
    {   Satellite S1(101,500);
            Satellite S2(102,600);
              SpaceObject* missionPtr= &S1;
                missionPtr->performChecking(); //This will call the performChecking function of the Satellite class because of dynamic dispatch, even though we are using a pointer of type SpaceObject, it will call the overridden function in the Satellite class at runtime.
                S1.display();
                    S2.display();
                        Satellite::ShowMissionStatus();}
    cout<<endl;{
          SpySatellite SS1(201,700,50);
            SpySatellite SS3(202,800,100);
                SS3.takephoto();
                     Satellite::ShowMissionStatus();
    }
    cout<<endl;
    {
         SpaceStation ST1(301,1000,10,80);
            ST1.conductExperiment();
            MissionController(&ST1); //Passing the address of the SpaceStation object to the MissionController function, which takes a pointer to a SpaceObject as an argument. This will allow us to call the performChecking function of the SpaceStation class through dynamic dispatch.
               SpaceObject* missionPtr2=&ST1;
                 missionPtr2->performChecking(); //This will call the performChecking function of the SpaceStation class because of dynamic dispatch, even though we are using a pointer of type SpaceObject, it will call the overridden function in the SpaceStation class at runtime. 
                   Satellite::ShowMissionStatus();
    }

    cout<<endl;
        SpaceObject SO5;
            SO5.rebootSystem();
                SpaceObject SO7;
                    SO7.performChecking();


    //We are calling static member func here because it belongs to the class and not to any specific object, so we can call it using the class name and scope resolution operator without creating an object of the class.
    //calling the static member function ShowMissionStatus using the class name and scope resolution operator
    return 0;
}