int main() {
    radiologyDepartment* radiology=radiologyDepartment::GetInstance();
    vector<labDepartment*> labs;
    labs.push_back(new labDepartment);
    secretaryCommand::initializeTestDepartments(radiology,&labs);
    baseClinic* endo = new endocrinologyClinic;
    baseClinic* card = new cardiologyClinic;
    baseClinic* orth = new orthopedicsClinic;
    endo->assignDoctor(new endocrinologist);
    card->assignDoctor(new cardiologist);
    orth->assignDoctor(new orthopedist);
    secretary endoSecretary(endo);
    secretary cardSecretary(card);
    secretary orthSecretary(orth);
    drugRecord record;
    bool endLoop=false;

    while(!endLoop) {
        while(true) {
            string result="";
            cout<<"Please enter number of the option:"<<endl;
            cout<<"1) New patient"<<endl;
            cout<<"2) Warn patients for a drug."<<endl;
            cout<<"3) Exit"<<endl;
            cin>>result;
            if(result=="1") {
                break;
            }
            else if(result=="2") {
                while(true){
                    string result="";
                    cout<<"Please enter the ID of the drug that you want to be informed:"<<endl;
                    cout<<"For drugA press 0"<<endl;
                    cout<<"For drugB press 1"<<endl;
                    cout<<"For drugC press 2"<<endl;
                    cout<<"For drugD press 3"<<endl;
                    cout<<"Press - to exit."<<endl;
                    cin>>result;
                    if(result == "0"){
                        record.informAllPatients(0);
                    }
                    else if(result == "1"){
                        record.informAllPatients(1);
                    }
                    else if(result == "2"){
                        record.informAllPatients(2);
                    }
                    else if(result == "3"){
                        record.informAllPatients(3);
                    }
                    else if(result == "-"){
                        endLoop= true;
                        break;
                    }
                }

            }
            else if(result=="3") {
                endLoop=true;
                break;
            }
        }
        if(!endLoop) {
            //patient demographics... will be asked and created here.
            patient* Patient=new patient("Patient1",new demographicInfo,new baseInsurance,new vector<baseTest*>);
            secretary* secretaryForClinic;
            while (true)
            {
                string result;
                cout<<"Choose which clinic to go:"<<endl;
                cout<<"1)Endocrinology Clinic"<<endl;
                cout<<"2)Orthopedics Clinic"<<endl;
                cout<<"3)Cardiology Clinic"<<endl;
                cin>>result;
                if(result=="1") secretaryForClinic=&endoSecretary;
                else if(result=="2") secretaryForClinic=&orthSecretary;
                else if(result=="3") secretaryForClinic=&cardSecretary;
                else
                {
                    cout<<"Wrong input."<<endl;
                    continue;
                }
                secretaryForClinic->acceptNewPatient(Patient);
                break;
            }
            while (true)
            {
                string result;
                cout<<"Choose what do you want secretary to do:"<<endl;
                cout<<"1)Check patient's tests"<<endl;
                cout<<"2)Ask for directions of other clinics."<<endl;
                cout<<"3)Ask for appointment"<<endl;
                cout<<"4)See the doctor."<<endl;
                cout<<"5)Patient wants to leave."<<endl;
                cin>>result;
                if(result=="5") {
                    cout<<"Patient leaves the clinic.";
                    break;
                }
                else if (result=="1") {
                    secretaryCommand* checkTestCommand = new checkTests(secretaryForClinic->getAssignedClinic(),Patient);
                    secretaryForClinic->acceptRequest(checkTestCommand);
                    continue;
                }
                else if(result=="2") {
                    secretaryCommand* directionsCommand = new askForClinics(secretaryForClinic->getAssignedClinic(),Patient);
                    secretaryForClinic->acceptRequest(directionsCommand);
                    continue;
                }
                else if(result=="3") {
                    secretaryCommand* appointmentCommand = new askForAnAppointment(secretaryForClinic->getAssignedClinic(),Patient);
                    secretaryForClinic->acceptRequest(appointmentCommand);
                    continue;
                }
                else if(result=="4") {
                    secretaryCommand* doctorCommand = new seeDoctor(secretaryForClinic->getAssignedClinic(),Patient);
                    secretaryForClinic->acceptRequest(doctorCommand);
                    continue;
                }
                else {
                    cout<<"Wrong input"<<endl;
                    continue;
                }
            }
            record.addPatientToRecord(Patient);
        }
    }

    return 0;
}
