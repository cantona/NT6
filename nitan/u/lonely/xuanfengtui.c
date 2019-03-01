#include <ansi.h>

void create()
{
        seteuid(getuid());
}

object book = find_object("/clone/lonely/book/xuanfengtui");

object get_owner()
{
    object owner;
    if(objectp(book)) {
        owner = environment(book);
        if(owner->is_character()) return owner;
    }
    return 0;
}

object book_owner = get_owner();
nosavestringbook_owner_name=(objectp(book_owner) && userp(book_owner))?query("name", book_owner):"某人";

int do_rumor(string arg)
{
    CHANNEL_D->do_channel(this_object(), "rumor", arg);
    return 1;
}

int get_book()
{
    if(objectp(book)) destruct(book);
    if(objectp(book_owner) && userp(book_owner)) book_owner->unconcious();
    do_rumor("聽說" + book_owner_name + "精神失常，旋風掃葉腿法被扔進了路邊的垃圾箱！");
    return 1;
}

nosave mixed *story = ({
        "黃藥師：蓉兒，近來江湖中出現了許多人偷學我桃花島的旋風掃葉腿法，甚是可恨！",
        "黃蓉：很容易啊，我讓江湖上提到旋風掃葉腿就怕。",
        (: do_rumor, "江湖傳言：東海桃花島開放，歡迎各路人士前來觀光旅遊。" :),
        "桃花島",
        "遊客甲：桃花影落飛神劍，碧海潮生按玉簫。",
        "遊客乙：果然景色優美！",
        "黃蓉：實乃居家旅遊的必來之處。",
        "桃花島眾弟子齊施──旋風掃葉腿！",
        "遊客：各位這是在表演節目麼？",
        "黃蓉：啊，各位可知，這桃花島上遍地桃花，一旦開花，地上滿是花瓣，打掃起來甚是不易！",
        "黃蓉：為此，我爹爹特意開發了桃花島專用掃地武學──旋風掃葉腿！",
        "眾遊客：啊，原來是打掃衛生的。",
        "黃蓉：對！清除垃圾保護環境做一名環保工人的必備武學。",
        "黃藥師、眾弟子暈倒......",
        "數日後，江湖上",
        "路人甲：看見沒，又是個練旋風掃葉腿的。",
        "路人乙：別去管他，那是用來掃地的。",
        "路人丙：掃地也是一份很有前途的職業啊，哪裡都需要，不愁下崗啊！",
        book_owner_name + "汗津：旋風掃葉腿＝掃地！！！",
        (: get_book :),
});

string prompt() { return HIW "【武林軼事】" NOR; }

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}
