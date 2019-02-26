#include <ansi.h>

#define XBOOK_DIR "/clone/lonely/book/"
int get_book();
int get_book2();

nosave mixed *story = ({
        "王語焉：公子，聽説表哥正在修煉參合指，欲找你報仇，你的六脈神劍也修煉一下吧！",
        "段譽：這個.........",
        "段譽：冤家宜解不宜結，何況兇毆鬥殺，有違國法，若教官府知道，大大的不便。",
        "木婉清：.............真是一塊爛木頭！",
        "鍾靈：難道慕容公子要搶走王姐姐你也不管麼？？？",
        "段譽：這個...這個...",
        "王語焉：你真的不管！！！",
        "段譽：不是不是，只是我家經絡學流落江湖，缺了它，無法修煉啊！",
        "木婉清：這倒是無妨，明天我們就重出江湖，尋找經絡學！！",
        "鍾靈：好啊好啊，正好出去玩玩！",
        "段譽：啊！你們都去！！！",
        "木婉清：當然！不然放你一個人出去，不知又找幾個姐姐回來！",
        "段譽：................",
        "數日後",
        (: get_book :),
        "段譽：這位兄台，小生段譽，我家經絡學你也看了許久，不知可否送還於我？",
        "某人：..........",
        "木婉清：跟他廢話這麼多！！看我的袖箭！！",
                (: get_book2 :),
        "某人慘叫一聲：啊！",
        "聽説某人慘遭毒手，經絡學被奪！",
});

string *books = ({
        "jingluoxue1",
        "jingluoxue2",
        });

string prompt() { return HIW "【武林軼事】" NOR; }

object ob;

void create()
{
        seteuid(getuid());
}

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

int get_book()
{
        int i = random(2);

        ob = find_object(XBOOK_DIR + books[i]);
                if(!objectp(ob)) ob = find_object(XBOOK_DIR + books[!i]);
                if(!objectp(ob)) {
                        story = allocate(20);
                        story[15] = "段譽：這幾日遊歷了大好河山，實乃快哉！";
                        story[16] = "木婉清：書都沒有找到，就知道玩，沒出息。";
                        story[17] = "鍾靈：嘻嘻，不會呀，我覺得這些天玩的蠻開心的。";
                        story[18] = "段譽：還是靈兒最知我心意。";
                        story[19] = "段譽一行人最後無功而反。";
                }
                return 1;
}

int get_book2()
{
        object owner;
        if(objectp(environment(ob)) && userp(environment(ob))) {
                owner = environment(ob);
                tell_object(owner, "只見一道寒光，一根袖箭正中你胸口。\n");
                owner->unconcious();
        }
        destruct(ob);
                return 1;
}
