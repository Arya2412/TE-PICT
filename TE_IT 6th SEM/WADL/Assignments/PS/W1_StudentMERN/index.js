import express from "express";
import mongoose from "mongoose";
import {studentModel} from "./student.js"

const app=express()

app.use(express.json())

mongoose.connect("mongodb+srv://SHUBZ:shubz@cluster0.kviaing.mongodb.net/subject?retryWrites=true&w=majority")

app.get("/getMoreThan25InAll", async function (request, response) {
    try {
      // Check if the database connection is established before querying the studentModel
  
      const students = await studentModel.find({
        WAD_Marks: { $gt: 25 },
        CC_Marks: { $gt: 25 },
        DSBDA_Marks: { $gt: 25 },
        CNS_Marks: { $gt: 25 },
        AI_Marks: { $gt: 25 }
      }, { Name: 1 });
  
      // creating view for browser
      let html = "The List Of Students Name Who Got More Than 25 Marks In All Subjects:<ul>";
      students.forEach(function (student) {
        html += "<li>" + student.Name + "</li>";
      });
      html += "</ul>";
      response.send(html);
    } catch (error) {
      response.status(500).send("An error occurred: " + error.message);
    }
  });

app.get("/getmore25",async function(req,res){
    const student=await studentModel.find({
        WAD_Marks:{$gt:25},
        CC_Marks:{$gt:25},
        CNS_Marks:{$gt:25},
        DSBDA_Marks:{$gt:25},
        AI_Marks:{$gt:25}
    },{Name:1})
    let html="Got 25 or more"
    student.map(function(student)
    {
        html+="<li>"
        html+=student.Name
        html+="</li>"
    })
    res.send(html)
})

// c) insert name and all data post method

app.post("/insertData",async(req,res)=>{
    const arraydata=req.body;
    const data=[]

    arraydata.forEach(input => {
        const {Name,Roll_No,WAD_Marks,CC_Marks,DSBDA_Marks,CNS_Marks,AI_marks}=input;
        data.push({Name,Roll_No,WAD_Marks,CC_Marks,DSBDA_Marks,CNS_Marks,AI_marks});
    });

    const result=await studentModel.insertMany(data)
    res.send(result);
})

// d.  Display total count of documents and List all the documents in browser.

app.get("/displayCount",async(req,res)=>{
    const documents=await studentModel.find({})
    res.send({"Total Count":documents.length,documents})
})

// e.  List the names of students who got more than 20 marks in DSBDA Subject in browser.

app.get("/dsbdaGT20",async(req,res)=>{
    const students=await studentModel.find({DSBDA_Marks:{$gt:20}},{Name:1})
    res.send(students)
})

// f.  Update the marks of Specified students by 10

app.put("/update10Marks/:studentID", async function (request, response) {
    const studentID = request.params.studentID
    const student = await studentModel.findOneAndUpdate({ _id: studentID }, 
        { $inc: { WAD_Marks: 10, CC_Marks: 10, DSBDA_Marks: 10, CNS_Marks: 10, AI_Marks: 10 } }, 
        { new: true })
    response.send(student)
})

// app.put("/updateMark10/:zName",async(req,res)=>{
//     const pName=req.params.zName;
//     // const data=await studentModel.findOne({pName});
//     // console.log(data)

//     try{
//         const student = await studentModel.findOneAndUpdate(
//             {Name:pName},
//             {$inc:{WAD_Marks: 10, CC_Marks: 10, DSBDA_Marks: 10, CNS_Marks: 10, AI_Marks: 10}},
//             {new:true})

//             res.send(student);
//     }catch(e){
//         console.log(e)
//         res.send(e)
//     } 
// })

// f.  Update the marks of Specified students by 10.

// app.get("/moreThan25",async(req,res)=>{
//     const student= await studentModel.find({
//         WAD_Marks:{$gt:25},
//         CC_Marks:{$gt:25},
//         DSBDA_Marks:{$gt:25},
//         CNS_Marks:{$gt:25},
//         AI_Marks:{$gt:25}
//     },{Name:1})

//     // let html="Students more than 25 Marks:"

//     // student.map((stud)=>{
//     //     html=html+"<li>"
//     //     html= html+student.Name
//     //     html=html+"</li>"
//     // })

//     res.json(student)
// })



app.listen(3001,()=>{
    console.log("Server is Running")
})