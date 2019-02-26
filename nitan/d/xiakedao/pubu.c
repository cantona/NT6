// pubu.c 瀑布

inherit ROOM;

#include <ansi.h>

int do_jump(string arg);
int do_plump(string arg);
void create()
{
        set("short", "瀑布");
        set("long", @LONG
你猛聽得水聲響亮，轟轟隆隆，便如潮水大至一般，抬頭一看，
只見一條大瀑布(pubu)，猶如銀河倒懸，從高崖上直瀉下來下面是萬
丈懸崖(xuanya)，雲霧瀰漫，望不到盡頭!!!
LONG  );
        set("exits", ([ /* sizeof() == 3 */
                "northdown" : __DIR__"road4",
        ]));
        set("outdoors", "xiakedao");
        set("item_desc",([
            "pubu"   : "你仔細一看，瀑布裏面好像有出口，你似乎可以跳(jump)進去。\n",
            "xuanya" : "下面瀰漫着煙霧，什麼也看不見，你可不要跳(plump)下去呀！\n",
        ]) );
        set("no_clean_up", 0);
        set("coor/x", -3000);
        set("coor/y", -22060);
        set("coor/z", 50);
        setup();
}

void init()
{
        add_action("do_jump","jump");
        add_action("do_plump","plump");
}
int do_jump(string arg)
{
        int n;
        n = this_player()->query_skill("dodge",1);
        if( !arg || arg!= "pubu" )
          {
          write("不要在這裏亂跳!\n");
          return 1;
        }
message_vision("$N在瀑布前站定，深呼一口氣，突然躍起。\n", this_player());
        if(n >=80)
        {
message_vision("只見$N腳尖一點地，身子輕飄飄的躍進瀑布之中。\n", this_player());
            this_player()->move(__DIR__"yongdao1");
        }
        else if(n >=50)
        {
message_vision("只見$N使出全身的力量，身子再空中搖搖惶惶，終於落在瀑布裏面。\n", this_player());
           this_player()->move(__DIR__"yongdao1");
        }
        else
        message_vision("只見$N高高躍起，還差很遠呢! \n", this_player());
        return 1;

}
int do_plump(string arg)
{
        object ob;
        int new_gin;

        ob = this_player();
        new_gin=random(query("max_gin", ob)*3);
        if( new_gin>query("gin", ob))new_gin=query("gin", ob)+1;
        if( !arg || arg!= "down")
        {
            write("你要跳什麼呀? \n");
            return 1;
        }
        tell_object(ob,HIR"你不加思索，縱身跳下了懸崖。\n"NOR);
        message("visoin",NOR"只見"+query("name", ob)+"縱身跳下了懸崖。\n"NOR,environment(ob),ob);
        if( (random(query("kar", ob))<15) && (ob->query_skill("dodge",1)<30) )
        {
            ob->die();
            return 1;
        }
        addn("gin", 0-new_gin, ob);
        ob->move(__DIR__"yadi");
        return 1;
}