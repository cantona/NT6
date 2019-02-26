// Code of ShenZhou
// Ryu, 5/10/97

inherit ROOM;

void create()
{
        set("short", "仙人洞");
        set("long", @LONG
路東的一座陡峭絕險的石峯(feng)腰間，有一石洞，距地數十尺。
峯腳是浪濤滾滾的塔勒奇河。洞口青松環列，洞頂刻有『財壽洞』三
個紅漆大字。據傳數百年前，一位來自中原的道人，在這險峯間鑿出
此洞。
LONG );
        set("exits", ([
                "south" : "/d/xingxiu/ertai",
        ]));
        set("cost", 2);
        set("outdoors", "tianshan");

        setup();
}
void init()
{
        add_action("do_climb", "climb");
}

int do_climb(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg=="" )
                return 0;
        if( arg=="feng")
        {
        if (me->query_skill("dodge") < 50){
                    write("你試圖攀上石峯，無奈身法不夠敏捷，只好做罷。\n");
                return 1;
                }
                else {
                    write("你一縱身順着石峯爬了上來。\n");
                    message("vision",
                             me->name() + "一縱身順着石峯攀了上去。\n",
                             environment(me), ({me}) );
                    me->move("/d/xingxiu/xrdong1");
                    message("vision",
                             me->name() + "從下面爬了上來。\n",
                             environment(me), ({me}) );
                return 1;
         }
     }
}
