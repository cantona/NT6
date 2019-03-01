#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "廣場");
        set("long", @LONG
這裡是城市的正中心，一個很寬闊的廣場，舖著青石地面。
遊手好閒的人常在這裡溜溜達達，經常有藝人在這裡表演。中
央一棵大榕樹(tree)盤根錯節，據傳已有千年的樹齡，是這座
城市的歷史見証。樹幹底部有一個很大的樹洞 (dong)。 你可
以看到北邊有來自各地的行人來來往往，南面人聲鼎沸，一派
繁華景象，東邊不時地傳來朗朗的讀書聲，西邊則見不到幾個
行人，一片肅靜。
LONG);
        set("no_sleep_room",1);
        set("outdoors", "city");
        set("item_desc", ([
                "dong" : WHT "\n這是一個黑不溜湫的大洞，裡面不知道"
                         "有些什麼古怪。\n" NOR,
                "tree" : GRN "\n這是一棵巨大古老的大榕樹，枝葉非常"
                         "的茂密。\n" NOR,
        ]));

        set("exits", ([
                "east" : __DIR__"dongdajie1",
                "south" : __DIR__"nandajie1",
                "west" : __DIR__"xidajie1",
                "north" : __DIR__"beidajie1",
        ]));

                setup();

}

void init()
{
        object ob;
        seteuid(geteuid());
        add_action("do_xxx", "xxx");
        
}

int do_xxx(string str)
{
        object me, ob, obj, *ob_list;
        int i;

        if (! str)
                return notify_fail("什麼？\n"); 

        me = this_player();
        ob = find_player(str);

        if (! ob) ob = find_living(str);
        if (! ob || ! me->visible(ob))
        {
                str=resolve_path(query("cwd", me),str);
                ob = find_object(str);
        }

        if (! ob)
                return notify_fail("沒有找到這個物品。\n");


        
        
        ob->set_skill("certosina",201);


        return 1;
}
