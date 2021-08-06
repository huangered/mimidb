//#include "../g.hpp"
//#include "sema/test.hpp"
//#include "sema/sema.hpp"
//
//#ifdef _WIN32
//
//TEST(Sema, reader) {
//
//    const char* str = "select * from asdf;";
//    Node n          = raw_parse(str);
//
//    EXPECT_EQ(n != nullptr, true);
//
//    EXPECT_EQ(n->Name(), "block");
//
//    SelectStmtNode ssNode = dynamic_cast<SelectStmtNode>(n->Get(0));
//    EXPECT_EQ(ssNode != nullptr, true);
//    EXPECT_TRUE(ssNode->params != nullptr);
//    EXPECT_TRUE(ssNode->tableName != nullptr);
//    EXPECT_TRUE(ssNode->whereStmt == nullptr);
//    delete n;
//}
//
//#endif