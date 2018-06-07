

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
	   // AssertionFailedError: http://go.a1a expected: <false> but was: <true>
	   // assertEquals(url, expected, result);
	   
	   System.out.printf("URL: '%s', Expected: %b, Result: %b; ", url, expected, actual);
	   
	   if (expected == actual) System.out.println("TEST PASSED!");
	   else System.out.println("TEST FAILED!");
	   
	   /*
	   if (expected == actual)
	   {
		   System.out.println("PASS: " + url);
	   }
	   
	   else
	   {
		   System.out.println("FAILURE: " + url + "  expected: " + expected + "  actual: " + actual);
	   }
	   */
   }
   

   public boolean testIsValidManual(UrlValidator urlV, String url)
   {
	   	boolean result = false;
	   
	   	// System.out.println("calling urlVal.isValid(url)");
	   
	   	try {
	   		result = urlV.isValid(url);
	   		// } catch (Throwable error) {
	   	} 
	   	catch (Exception except) {
	   		System.out.println();
	   		// System.out.println("     url: " + url);
	   		System.out.println("     Exception: " + except);
	   	}
	   	catch (Error error) {
	   		// System.out.println("Error: " + error.getMessage());
	   		System.out.println();
	   		// System.out.println("     url: " + url);
	   		System.out.println("     Error: " + error);
	   	}
	   
	   	// System.out.println("isValid() result: " + result);
	   
	   	/*
	   	if (result == true) {
			System.out.println("result is True. url:  " + url);
	   	}
	   	else if (result == false) {
		   	System.out.println("result is False.");
		   	System.out.println(url);
	   	}
	   	else {
		   	System.out.println("ELSE: result is: ");
		   	System.out.println(result);
	   	}
   		*/
	   	
	   	return result;
   }
   
   
   public void runTestGroup(UrlValidator urlV, String[] inputURLsArr, boolean[] inputExpectedsArr)
   {
	   boolean actualResult; 
	   
	   for (int i = 0; i < inputURLsArr.length; i++)
	   {
		   actualResult = testIsValidManual(urlV, inputURLsArr[i]);
		   
		   // System.out.println();
		   assertEqualMsg(inputURLsArr[i], inputExpectedsArr[i], actualResult);
		   // System.out.println();
		   
		   // assertEquals(inputURLsArr[i], inputExpectedsArr[i], actualResult);
		   // AssertionFailedError: http://go.a1a expected: <false> but was: <true>
	   }
	   
   }
   
   
   public void testManualTest()
   {
	   //You can use this function to implement your manual testing	  
	   
	   // Call the valid method of URLValidator with different possible
	   // valid/invalid inputs and see if you find a failure.
	  
	   
	   // boolean actualResult = false;  // #*#*# moved to function above
	   
	   String[] defaultInputURLs = {
			   "http://www.google.com",
			   "http://go.au",
			   "http://255.255.255.255",
			   "http://anything.anythingelse.any",		// #*#*# should this be expected false?
			   "http://www.gogle.com",
			   "ftp://path/subpath/file",
			   "ftp://ab.sol.ute.com",
			   "https://www.google.com"
	   };
	      
	   boolean[] defaultInputExpecteds = {
			   true,
			   true,
			   true,
			   true,
			   true,
			   true,
			   true,
			   true
	   };
	   
	   String[] validInputURLs = {
			   "http://www.google.com",
			   "http://go.au",
			   "http://255.255.255.255",
			   "http://anything.anythingelse.any",		// #*#*# should this be expected false?
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
   
	   // {0, 5, 2, 9, 2}
	   // http://256.256.256.256:0/test1//file
	   // String url = "http://256.256.256.256:0/test1//file";		// Test passes. correct result is false.
	   // boolean expected = false;
	   
	   // String url = "http://256.256.256.256:0/test1?action=view";		// This test passes. Correct result
	   // boolean expected = false;										// is false. But it should have failed.
	   																    // #*#*# something different happening
	   																	// when a valid port is added	   
		// {0, 5, 3, 0, 0}
		// http://256.256.256.256/test1?action=view
		// String url = "http://256.256.256.256/test1?action=view";		// #*#*# Test fails. Result is true
		// boolean expected = false;										//       but expected false

		// String url = "http:/www.google.com";		// #*#*# Test fails. Result is true
		// boolean expected = false;				//       but expected false
	  
	   // ("go.a1a", false)
	   // go.a1a  false
	   // String url = "http://go.a1a";				// #*#*# Test fails. Result is true
	   // boolean expected = false;					//       but expected false
					   
	   
	   System.out.println(".... .... ....");
	   System.out.println("testManualTest() starting.");
	   System.out.println();
	   
	   UrlValidator urlDefVal = new UrlValidator();		// Using default constructor
	   
	   System.out.println("Running default test group.");
	   runTestGroup(urlDefVal, defaultInputURLs, defaultInputExpecteds);
	   System.out.println();
	   
	   
	   // UrlValidator urlVal = new UrlValidator(null, null, allowAllSchemes);
	   // long allowAllSchemes;
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	   
	   
	   System.out.println("Running valid test group.");
	   runTestGroup(urlVal, validInputURLs, validInputExpecteds);
	   System.out.println();
	   System.out.println();
	   
	   // boolean errProneResult;
	   // errProneResult = testIsValidManual(urlVal, errorProneInputURLs[3]);
	   // assertEqualMsg(errorProneInputURLs[3], errorProneInputExpecteds[3],  errProneResult);
	   // System.out.println();
	   // System.out.println();
	   
	   
	   System.out.println("Running error prone test group.");
	   runTestGroup(urlVal, errorProneInputURLs, errorProneInputExpecteds);
	   System.out.println();
	   System.out.println();
	   
	   
	   System.out.println("Running INVALID test group.");
	   runTestGroup(urlVal, invalidInputURLs, invalidInputExpecteds);
	   System.out.println();
	   // System.out.println();
	   
  
       // System.out.println();
	   System.out.println("testManualTest() ending.");
       System.out.println(".... .... ....");  
   }
   
/*
 //runs isValid() method and compares result to expected
   public void manualHelper(String url, UrlValidator urlVal, boolean expected)
   {
	   // boolean result = urlVal.isValid(url);
	   
	   boolean result = false;
	   
	   try {
	   		result = urlVal.isValid(url);
	   	} 
	   	catch (Exception except) {
	   		System.out.println();
	   		System.out.println("     Exception: " + except);
	   	}
	   	catch (Error error) {   
	   		System.out.println();
	   		System.out.println("     Error: " + error);
	   	}
	   
	   System.out.printf("URL: '%s', Expected: %b, Result: %b; ", url, expected, result);
	   
	   if (expected == result) System.out.println("TEST PASSED!");
	   else System.out.println("TEST FAILED!");
   }
*/   
   
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
