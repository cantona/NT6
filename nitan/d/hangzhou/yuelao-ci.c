// Room: /yuelaoci.c
#define QIUQIAN "/d/hangzhou/qiuqian"

#include <ansi.h>

#include <room.h>
inherit ROOM;
int is_chat_room() { return 1;}
void create(){
        set("short", "月老祠");
        set("long", @LONG
月老是神話中掌管姻緣的仙人，傳説他有紅線，若把它系在男女
朋方的腳上，雖仇人或相隔千里，終會結成姻緣。月老祠一間小院、
三五瓦屋。正屋中央的神龕裏坐着月下老人：紅風帽紅披肩，鶴髮童
顏，笑容滿面。神龕前面照例是供桌、香爐、燭台、籤筒，當然，蒲
團也是少不了的。兩旁一副黑漆的小對聯：願天下有情人，都成了眷
屬；是前生註定事，莫錯過姻緣。令人拍案叫絕。你可以在這裏求籤
（qiuqian）問一下姻緣情事。
LONG );
        set("no_fight", "1");
        set("no_steal", "1");
        set("no_sleep_room","1");

        set("exits", ([
                "south" : "/d/hangzhou/yuanyuan-tai",

        ]));
	set("coor/x", 770);
	set("coor/y", -1960);
	set("coor/z", 10);
	setup();
}
void init()
{
        add_action("do_qiuqian","qiuqian");
}

int do_qiuqian(string arg)
{
            object me;

        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;

        if( time()-query("last_qiuqian_time", me)<600 )
                return notify_fail("這麼頻繁的求籤幹嘛？心不誠則籤不靈，過十分鐘再來吧。\n");

        write(HIC "
你虔誠地向月老像拜了幾拜，口中唸唸有詞：“月老月老，賜給我好姻緣吧！”
你閉着眼擎了支籤，又祈禱了一會，這才睜開眼睛看籤文。\n
" NOR, me);
        write(HIC "簽上寫着：" + QIUQIAN->query_qiuqian() + "。\n" NOR, me);
        set("last_qiuqian_time", time(), me);
        return 1;
}