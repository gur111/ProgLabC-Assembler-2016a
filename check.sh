echo "Cleaning last executable files"
make clean
echo "Remaking project"
make

echo "In all files test2 should overflow"

echo ""
echo ""
echo "Testing on files: test1 test2 test3"
./FINAL_PROJECT test1 test2 test3
echo ""
echo ""

echo "Testing on files: test1 test6 test3"
./FINAL_PROJECT test1 test6 test3
echo ""
echo ""
echo "Testing on files: test7 test6 test3"
./FINAL_PROJECT test7 test6 test3
echo ""
echo ""
echo "Testing on files: test5 test3 test7"
./FINAL_PROJECT test5 test3 test7
echo ""
echo ""
echo "Testing on files: test1 test2 test3 test4 test5 test6 test7"
./FINAL_PROJECT test1 test2 test3 test4 test5 test6 test7
echo ""
echo ""
echo "Testing on files: test1 ugabuga bloop bleep"
./FINAL_PROJECT test1 ugabuga bloop bleep
echo ""
echo ""
echo "Testing on files: this_file_is_not_valid test1"
./FINAL_PROJECT this_file_is_not_valid test1
echo ""
echo ""
echo "Testing on files: test1.as"
./FINAL_PROJECT test1.as

echo ""
echo ""
echo ""
echo "Testing file by file:"
echo ""
echo ""
var="test1"
echo "$var + output files"
./FINAL_PROJECT $var
cat $var.ob
echo "#############Externals##############"
cat $var.ext
echo "#############Entries################"
cat $var.ent

echo ""
echo ""
var="test2"
echo "$var + output files (Should overflow)"
./FINAL_PROJECT $var
cat $var.ob
echo "#############Externals##############"
cat $var.ext
echo "#############Entries################"
cat $var.ent

echo ""
echo ""
var="test3"
echo "$var + output files"
./FINAL_PROJECT $var
cat $var.ob
echo "#############Externals##############"
cat $var.ext
echo "#############Entries################"
cat $var.ent

echo ""
echo ""
var="test4"
echo "$var + output files"
./FINAL_PROJECT $var
cat $var.ob
echo "#############Externals##############"
cat $var.ext
echo "#############Entries################"
cat $var.ent

echo ""
echo ""
var="test5"
echo "$var + output files (No .ext for this file)"
./FINAL_PROJECT $var
cat $var.ob
echo "#############Externals##############"
cat $var.ext
echo "#############Entries################"
cat $var.ent

echo ""
echo ""
var="test6"
echo "$var + output files"
./FINAL_PROJECT $var
cat $var.ob
echo "#############Externals##############"
cat $var.ext
echo "#############Entries################"
cat $var.ent

echo ""
echo ""
var="test7"
echo "$var + output files (No .ext for this file)"
./FINAL_PROJECT $var
cat $var.ob
echo "#############Externals##############"
cat $var.ext
echo "#############Entries################"
cat $var.ent

rm *.ent *.ext *.ob
