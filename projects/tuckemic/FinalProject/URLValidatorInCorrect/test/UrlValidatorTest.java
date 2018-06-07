
// UrlValidatorTest.java
/*
 * CS362
 * Final Project: Part-B
 * Team: Christa Wright - wrighch3, Jorge Guzman Nader - guzmannj, Michael Tucker - tuckemic
 * Date: 6/11/2018
 * Description: Testing of Apache Commons URLValidatorInCorrect
 */

import junit.framework.TestCase;
import java.util.Random;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!


public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   public void assertEqualMsg(String url, boolean expected, boolean actual)
   { 
	   if (expected == actual) 
	   {
		   	System.out.printf("TEST PASSED! ");
	   }
	   else 
	   {
		   	System.out.printf("TEST FAILED! ");
	   }
	   
	   System.out.printf("Expected: %b, Result: %b, URL: '%s'\n", expected, actual, url);
   }
   

   public boolean testIsValidManual(UrlValidator urlV, String url)
   {
	   	boolean result = false;
	   
	   	try {
	   		result = urlV.isValid(url);
	   	} 
	   	catch (Exception except) {
	   		System.out.println();
	   		System.out.println("     Exception: " + except);
	   	}
	   	catch (Error error) {
	   		System.out.println();
	   		System.out.println("     Error: " + error);
	   	}	   	
	   	return result;
   }
   
   
   public void runTestGroup(UrlValidator urlV, String[] inputURLsArr, boolean[] inputExpectedsArr)
   {
	   boolean actualResult; 
	   
	   for (int i = 0; i < inputURLsArr.length; i++)
	   {
		   actualResult = testIsValidManual(urlV, inputURLsArr[i]);
		   
		   assertEqualMsg(inputURLsArr[i], inputExpectedsArr[i], actualResult);
	   }
	   
   }
   
   
   public void testManualTest()
   {
	   //You can use this function to implement your manual testing	  
	   
	   // Call the valid method of URLValidator with different possible
	   // valid/invalid inputs and see if you find a failure.
	   
	   String[] defaultInputURLs = {
			   "http://www.google.com",
			   "http://go.au",
			   "http://255.255.255.255",
			   "http://anything.anythingelse.any",
			   "http://www.gogle.com",
			   "ftp://path/subpath/file",
			   "ftp://ab.sol.ute.com",
			   "https://www.google.com"
	   };
	      
	   boolean[] defaultInputExpecteds = {
			   true,
			   true,
			   true,
			   false,
			   true,
			   true,
			   true,
			   true
	   };
	   
	   String[] validInputURLs = {
			   "http://www.google.com",
			   "http://go.au",
			   "http://255.255.255.255",
			   "http://www.gogle.com",
			   "http://www.google.com",
			   "http://go.com",
			   "http://0.0.0.0",
			   "http://255.255.255.255",
			   "http://255.com",
			   "http://www.google.com:80",
			   "http://www.google.com:65535",
			   "http://www.google.com/firstPath",
			   "http://www.google.com/$23h",
			   "http://www.google.com/test1/file",
			   "http://www.google.com?action=view",
			   "http://www.google.com?action=edit&mode=up" 
	   };
	      
	   boolean[] validInputExpecteds = {
			   true,
			   true,
			   true,
			   true,
			   true,
			   true,
			   true,
			   true,
			   true,
			   true,
			   true,
			   true,
			   true,
			   true,
			   true,
			   true,
			   true
	   };
	   
	   
	   String[] errorProneInputURLs = {
			   "htt://www.google.com",
			   "htt://www.google.com",
			   "ftp://www.go!gle.com",
			   "ftp://path/subpath/file",
			   "ftp://ab.sol.ute.com",
			   "https://www.google.com",
			   "file://",
			   "ftp://www.google.com",
			   "h3t://www.google.com"
	   };
	   
	   boolean[] errorProneInputExpecteds = {
			   false,
			   false,
			   false,
			   true,
			   true, 
			   true,
			   true,
			   true,
			   true
	   };
	   
	   
	   String[] invalidInputURLs = {
			   "3ht://www.google.com",
			   "://www.google.com",
			   "http://256.256.256.256:0/test1//file",
			   "http://256.256.256.256:0/test1?action=view",
			   "://go.a1a",
			   "3ht://256.256.256.256",
			   "http://256.256.256.256/test1?action=view",
			   "http:/www.google.com",
			   "http://256.256.256.256",
			   "http://1.2.3.4.5",
			   "http://go.a1a",
			   "http://1.2.3",
			   "http://",
			   "http://any..thing..any.0..1.",
			   "http://abc1.2.3",
			   "http://go.a",
			   "http://www.google.c",
			   "http://www.go!gle.com",
			   "http://www.g*ogle.com",
			   "http://www.googlecom",
			   "http:/www.google.com",
			   "http://256.256.256.256",
			   "http://",
			   "http://www.google.com:65636",
			   "http://www.google.com:-1",
			   "http://www.google.com/../",
			   "http://www.google.com/..//file",
			   "http://www.google.com!action=view",
			   "http://",	   
	   };
	      
	   boolean[] invalidInputExpecteds = {
			   false,
			   false,
			   false,
			   false,
			   false,
			   false,
			   false,
			   false,
			   false,
			   false,
			   false,
			   false,
			   false,
			   false,
			   false,
			   false,
			   false,
			   false,
			   false,
			   false,
			   false,
			   false,
			   false,
			   false,
			   false,
			   false,
			   false,
			   false,
			   false 
	   };
    
	   System.out.println("\nManual Tests starting.");
	   
	   UrlValidator urlDefVal = new UrlValidator();		// Using default constructor
	   
	   System.out.println("Manual Tests: Running default scheme test group.");
	   runTestGroup(urlDefVal, defaultInputURLs, defaultInputExpecteds);
	   System.out.println();
	   

	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	   
	   
	   System.out.println("Manual Tests: Running valid test group.");
	   runTestGroup(urlVal, validInputURLs, validInputExpecteds);
	   System.out.println();
	   System.out.println();
 
	   
	   System.out.println("Manual Tests: Running error prone test group.");
	   runTestGroup(urlVal, errorProneInputURLs, errorProneInputExpecteds);
	   System.out.println();
	   System.out.println();
	   
	   
	   System.out.println("Manual Tests: Running INVALID test group.");
	   runTestGroup(urlVal, invalidInputURLs, invalidInputExpecteds);
	   System.out.println();
   }
   
   
 //Test for the schemes
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing
       
	   System.out.println("\nInput Partitioning Test: URL Schemes");
	   
	   
       //URL validator
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       
       //Valid test cases
       String[]  checkAccept = {"http://"};
       
       //Invalid test cases
       String[] checkReject = {"http:/", "http::", ":://", ":/", "23://"};
       
       //Counter for test count and loop
       int count = 0;
       int i = 0;
       
       //Get the total length and internal length
       int totalLength = checkAccept.length + checkReject.length;
       int innerLen = 0;
       int outerLen = 0;
       
       //Count for test passed and failed
       int testPassed = 0;
       int testFailed = 0;
       
       //Loop to check for test cases
       for(i = 0; i < totalLength; i++){
           
           //Valid test cases
           if (outerLen < checkAccept.length){
               
               //Check the url string
               String[] stringURL = {"" + checkAccept[outerLen] + "www.oregonstate.edu"};
           
               
               //Valid test should pass
               if(urlVal.isValid(stringURL[0])){
                   
                   //For passed test cases
                   testPassed = testPassed + 1;
               }
           
               //If the test failed
               else{
                   
                   //For failed test cases
                   System.out.println("Test Failed for URL (Incorrect Reject) : " + stringURL[0]);
                   testFailed = testFailed + 1;
               }
               
                //Counter for accept test cases
               	outerLen = outerLen + 1;
            }
           
            //Invalid test cases
            else{
                
                //Check the url string
                String[] stringURL = {"" + checkReject[innerLen] + "www.oregonstate.edu"};
                
                //Invalid test should fail
                if(urlVal.isValid(stringURL[0])){
                    
                    //For failed test
                    System.out.println("Test Failed for URL (Incorrect Accept): " + stringURL[0]);
                    testFailed = testFailed + 1;
                }
                
                //If the test passed
                else{
                    
                    //For test passed
                    testPassed = testPassed + 1;
                
                }

                //Counter for reject test cases
                innerLen = innerLen + 1;
           }
           
           //Counter for total tests
           count = count + 1;
       }
       
       //Print out for test results
       System.out.println("Total Test: " + count);
       System.out.println("Passed Test: " + testPassed);
       System.out.println("Failed Test: " + testFailed);
   }
   

   
   
   /*
   public void testYourFirstPartition()
   {
	   //You can use this function to implement your First Partition testing	   

   }
   
   
   public void testYourSecondPartition(){
	   	//You can use this function to implement your Second Partition testing	   

   }
   		//You need to create more test cases for your Partitions if you need to 
   
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   */
   
}
