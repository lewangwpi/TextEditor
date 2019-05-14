#include "../textEditor/editClass.hpp"
#include <gtest/gtest.h>

class editClass_test : public testing::Test
{
public:
//	static void SetUpTestCase() { }
//	static void TearDownTestCase() { }
//	virtual void SetUp() { }	
//	virtual void TearDown() { }	
	editClass textEditor;
	string orgStr = "helloworld\n";
	string sstr = "CPP: ";
	string ndlStr = "o";
	int pos = 2;	
	int length = 3;
};

/** Test 'INSERT' Operation*/
TEST_F(editClass_test, insertString) {
	string cmpStr = orgStr.insert(pos, sstr);
	string testStr = textEditor.insertStr(sstr, pos);
	ASSERT_EQ(cmpStr, testStr);
}

TEST_F(editClass_test, insertEmptyString) {
	string cmpStr = orgStr.insert(pos, "");
	string testStr = textEditor.insertStr("", pos);
	ASSERT_EQ(cmpStr, testStr);
}

TEST_F(editClass_test, insertIdxOutOfRange) {
	try {
		string testStr = textEditor.insertStr(sstr, 1000000);
		FAIL() << "Expected idxOutOfRange exception not received." << endl;
	} catch (exception& e) {
		EXPECT_EQ(e.what(), string("Error(insertStr): Position index should be less than content size."));
	} catch (...) {
		FAIL() << "Unexpected exception caught." << endl;
	}
}

/** Test 'APPEND' operation*/
TEST_F(editClass_test, appendString) {
	string cmpStr = orgStr.substr(0, orgStr.size()-1) + sstr + "\n";
	string testStr = textEditor.appendStr(sstr);
	ASSERT_EQ(cmpStr, testStr);
}

TEST_F(editClass_test, appendEmptyString) {
	string testStr = textEditor.appendStr("");
	ASSERT_EQ(orgStr, testStr);
}

/** Test 'ERASE' string */
TEST_F(editClass_test, eraseString) {
	string cmpStr = orgStr.erase(pos,length);
	string testStr = textEditor.eraseStr(pos,length);
	ASSERT_EQ(cmpStr, testStr);
}

TEST_F(editClass_test, eraseEmptyString) {
	string cmpStr = orgStr.erase(pos,0);
	string testStr = textEditor.eraseStr(pos,0);
	ASSERT_EQ(cmpStr, testStr);
} 

TEST_F(editClass_test, eraseIdxOutOfRange) {
	try {
		string testStr = textEditor.eraseStr(10000,1);
		FAIL() << "Expected idxOutOfRange exception not received." << endl;
	} catch (exception& e) {
			EXPECT_EQ(e.what(), string("Error(eraseStr): Position index should be less than content size."));
	} catch (...) {
		FAIL() << "Unexpected exception caught." << endl;
	}
}

/** Test 'ERASE TRAIL' operation*/
TEST_F(editClass_test, eraseTrail) {
	string cmpStr = orgStr.erase(orgStr.size()-length-1, length);
	string testStr = textEditor.eraseTrail(length);
	ASSERT_EQ(cmpStr, testStr);
}

TEST_F(editClass_test, eraseTrailIdxOutOfRange) {
	try {
		string testStr = textEditor.eraseTrail(100000);
		FAIL() << "Expected idxOutOfRange exception not received." << endl;
	} catch (exception& e) {
		EXPECT_EQ(e.what(), string("Error(eraseTrail): Length should be less than content size."));
	} catch (...) {
		FAIL() << "Unexpected exception caught." << endl;
	}
}

/** Test 'REPLACE' operation */
TEST_F(editClass_test, replaceString) {
	string cmpStr = "hellCPP: wCPP: rld\n";
	string testStr = textEditor.replaceStr(ndlStr,sstr);
	ASSERT_EQ(cmpStr, testStr);
}

TEST_F(editClass_test, replaceWithEmptyString) {
	string cmpStr = "hellwrld\n";
	string testStr = textEditor.replaceStr(ndlStr,"");
	ASSERT_EQ(cmpStr, testStr);
}

TEST_F(editClass_test, replaceEmptyTargetString) {
	try {
		string testStr = textEditor.replaceStr("",sstr);
		FAIL() << "Expected idxOutOfRange exception not received." << endl;
	} catch (exception& e) {
		EXPECT_EQ(e.what(), string("Error(replaceStr): target string cannot be empty."));
	} catch (...) {
			FAIL() << "Unexpected exception caught." << endl;
	}
}

/** Test 'LOAD FILE' operation */
TEST_F(editClass_test, openNonExistFile) {
	try {
		textEditor.openFile("nonExistFile.txt");
		FAIL() << "Expected FileNotExist exception not received." << endl;
	} catch (exception& e) {
		EXPECT_EQ(e.what(), string("File does not exist"));
	} catch (...) {
			FAIL() << "Unexpected exception caught." << endl;
	}
}

/** Test 'UNDO' operation */
TEST_F(editClass_test, undoTest) {
	string testStr = textEditor.openFile("a.txt");
	string cmpStr = testStr;	
	testStr = textEditor.appendStr(sstr);
	testStr = textEditor.insertStr(sstr, pos);
	testStr = textEditor.eraseStr(pos,length);
	testStr = textEditor.eraseTrail(length);
	testStr = textEditor.replaceStr(ndlStr, sstr);	
	for (int i = 0; i < 5; i++ ) {
		testStr = textEditor.undoOP();
	}	
	ASSERT_EQ(cmpStr, testStr);	
}

TEST_F(editClass_test, undoStackOverflow) {
	try {
		string testStr = textEditor.appendStr("padding text");
		testStr = textEditor.undoOP();
		testStr = textEditor.undoOP();
		FAIL() << "Expected undoStackOverflow exception not received." << endl;
	} catch (exception& e) {
		EXPECT_EQ(e.what(), string("Error(undoBuff): target buffer is empty."));
	} catch (...) {
		FAIL() << "Unexpected exception caught." << endl;
	}

}

/** Test 'REDO' operation */
TEST_F(editClass_test, redoTest) {
	string testStr = textEditor.openFile("a.txt");
	testStr = textEditor.appendStr(sstr);
	testStr = textEditor.insertStr(sstr, pos);
	testStr = textEditor.eraseStr(pos,length);
	testStr = textEditor.eraseTrail(length);
	testStr = textEditor.replaceStr(ndlStr, sstr);
	string cmpStr = testStr;
	for (int i = 0; i < 5; i++ ) {
		testStr = textEditor.undoOP();
	}
	for (int j = 0; j < 5; j++) {
		testStr = textEditor.redoOP();
	}
	ASSERT_EQ(cmpStr, testStr);	
}

TEST_F(editClass_test, redoBeforeUndo) {
	try {
		string testStr = textEditor.appendStr("padding text");
		testStr = textEditor.redoOP();
		FAIL() << "Expected redoStackOverflow exception not received." << endl;
	} catch (exception& e) {
		EXPECT_EQ(e.what(), string("Error(redoBuff): target buffer is empty."));
	} catch (...) {
		FAIL() << "Unexpected exception caught." << endl;
	}
}

TEST_F(editClass_test, redoStackOverflow) {
	try {
		string testStr = textEditor.openFile("a.txt");
		testStr = textEditor.appendStr(sstr);
		testStr = textEditor.insertStr(sstr, pos);
		testStr = textEditor.eraseStr(pos,length);
		testStr = textEditor.eraseTrail(length);
		testStr = textEditor.replaceStr(ndlStr, sstr);
		string cmpStr = testStr;	
		for (int i = 0; i < 5; i++ ) {
			testStr = textEditor.undoOP();
		}
		for (int j = 0; j < 10; j++) {
			testStr = textEditor.redoOP();
		}
		FAIL() << "Expected redoStackOverflow exception not received." << endl;
	} catch (exception& e) {
		EXPECT_EQ(e.what(), string("Error(redoBuff): target buffer is empty."));
	} catch (...) {
		FAIL() << "Unexpected exception caught." << endl;
	}
}

/** main */
int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


































