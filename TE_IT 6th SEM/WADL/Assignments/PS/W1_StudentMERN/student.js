import mongoose from "mongoose";

const studentSchema=mongoose.Schema({
    Name:String, 
    Roll_No:Number, 
    WAD_Marks:Number, 
    CC_Marks:Number, 
    DSBDA_Marks:Number,
    CNS_Marks:Number,
    AI_marks:Number
},{versionKey:false,timestamps:true});

export const studentModel=mongoose.model("studentmarks",studentSchema);

