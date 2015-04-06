#ifndef SLS_NO_SQL

#include <animal/animal_game.h>
#include <gtest/gtest.h>
#include <sqlite3.h>
#include <string>

class SqlTests : public testing::Test {
 protected:
  sqlite3 *db;

  virtual void SetUp() {
    auto path = (char const *)"./test.db";
    ASSERT_EQ(SQLITE_OK, sqlite3_open(path, &db));
  }
  virtual void TearDown() { ASSERT_EQ(SQLITE_OK, sqlite3_close(db)); }
};

TEST_F(SqlTests, OpenTest) {
  EXPECT_NE((sqlite3 *)NULL, db);
  EXPECT_NE(nullptr, db);
}

TEST_F(SqlTests, MakeStatement) {
  const auto source = sls_get_create_table_sql();
  char *err = nullptr;
  auto rc = sqlite3_exec(db, source, nullptr, nullptr, &err);
  EXPECT_EQ(SQLITE_OK, rc);
  EXPECT_EQ(err, nullptr) << "errmsg = " << std::string(err);
}
TEST_F(SqlTests, TestInsert) {
  char const *fmt = (char const*)
        "INSERT INTO nodes(is_species, description)"
        "VALUES (%d, '%s');";
  auto source = sqlite3_mprintf(fmt, SLS_TRUE, "dog");
  ASSERT_NE(source, nullptr) << "sqlite3_mprintf produced nullptr";

  char *err = nullptr;
  auto rc = sqlite3_exec(db, source, nullptr, nullptr, &err);

  EXPECT_EQ(SQLITE_OK, rc);
  EXPECT_EQ(err, nullptr) << "errmsg = " << std::string(err);

  if (source) {
    free(source);
  }
}

#endif /* SLS_NO_SQL */
