# DynamicTest_Kyber_1
Dynamic Test of KyberSlash2. This is the Dynamic Test for Kyber, to Verify the existence of the Flaw called KyberSlash2 discovered in Dec 2023. 

In this file, the core code is included in the test_speed.c, under the ref folder. in the code, 2 different key groups are generated and the decapsulation time is recorded for 'NTEST + 1' times with relavent parameters including means and variance recorded. Then the TVLA value for two key groups is calculated based on the required means and vars for two keys.  

The other files related to Kyber, which cannot be transmitted to the github in the online page is transmitted to the 'master' branch. 
