#include <ansi.h>

void create()
{
        seteuid(getuid());
}

object book = find_object("/clone/lonely/book/zhenjing1");

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
nosave string book_owner_name = objectp(book_owner)?query("name", book_owner):"某人";

int do_rumor(string arg)
{
        CHANNEL_D->do_channel(this_object(), "rumor", arg);
        return 1;
}

string get_book()
{
        if(objectp(book)) destruct(book);
        if(objectp(book_owner) && userp(book_owner)) book_owner->unconcious();
        return book_owner_name + "被黃藥師打暈了。";
}

nosave mixed *story = ({
        "桃花島山洞",
        "黃藥師：老頑童，聽說江湖上" + book_owner_name + "得到了九陰真經上冊！你不是說真經上冊一直在你這麼？",
        "周伯通：哦，是麼？不可能吧......",
        "黃藥師：你騙了我這麼久！居然把真經給了別人！！！接我的碧海潮生曲！！",
        "周伯通：等等！！！我肚子痛！",
        "黃藥師：﹒#＄！%",
        "周伯通：黃老邪，不是我怕你！真經真的還在我這！！",
        "黃藥師：那拿出來讓我瞧瞧！",
        "周伯通：不行，我拿出來你就搶了！",
        "黃藥師：我看是你早就給人了！我們一同出去，若是讓我發現真經在別人那裡，哼哼~",
        "周伯通：怎麼樣？",
        "黃藥師：我就宰了你！",
        "周伯通：......（就你那能耐，呸，打的贏我嗎？）",
        (: do_rumor, "黃藥師與周伯通為九陰真經出了桃花島......" :),
        "三天後",
        (: get_book :),
        "黃藥師：如何，這就是從他身上搜出的真經！！！",
        "周伯通（翻了兩下）：明明是無字書啊！！",
        "黃藥師、" + book_owner_name + "：不可能！！！",
        book_owner_name + "心想：我都拿了3天，看了無數遍，如何可能是無字書？？？？？？",
        "黃藥師翻了兩下：真的無字書！！",
        "周伯通暗自偷樂：真經原本早就被我毀了！現在的都是我默寫出來的！\n"
        "我都用草汁寫在紙上，一見光3天後字跡就消失！任你黃老邪姦似鬼，還不是喝我的洗腳水！",
        "黃老邪：好，只要真經不在別人那裡就行，跟我回桃花島。",
        "周伯通：你......﹒#＄%",
});

string prompt() { return HIW "【武林軼事】" NOR; }

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}
