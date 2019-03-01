// Room: /d/yanziwu/chaosheng.c
// Date: Jan.28 2000 by Winder

inherit ROOM;

void create()
{
        set("short", "潮聲巖");
        set("long", @LONG
潮聲巖一半浸沒在水中。巖石大可丈許，內裡早被波浪掏空。一旦
潮水來時，水波相激，轟然做響，聲聞遠近。湖浪沖擊潮聲巖內壁，猛
然反濺回來，你一愣神，不自禁舉手想擋(dang)一下。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "enter"   : __DIR__"dong2",
        ]));
        set("coor/x", 1200);
        set("coor/y", -1280);
        set("coor/z", 0);
        setup();
}
void init()
{
        add_action("do_parry", "dang");
        add_action("do_parry", "parry");
}
int do_parry()
{
        object weapon, me = this_player();
        int skilllvl = me->query_skill("parry",1);
        int exp=query("combat_exp", me);
        if( query("qi", me)<10 )
                return notify_fail("你出手想擋，可是沒力氣啦，當場水淋滿頭。\n");
        addn("qi", -10, me);
        addn("eff_qi", -2, me);
        if (skilllvl < 50)
                return notify_fail("你出手想擋，可是來不及啦，浪頭蓋下，澆你個一頭濕。\n");
        if (skilllvl > 150)
                return notify_fail("擋什麼擋！這點小浪有什麼可怕的？\n");
        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("沒有用兵器，恐怕擋不住吧？\n");
        if ((skilllvl*skilllvl*skilllvl/10) < exp)
                me->improve_skill("parry", random(me->query_skill("parry",1)));
        return notify_fail("你提起"+query("name", weapon)+"，向浪頭揮去，一股罡氣將浪頭擊得四散濺落。\n");
}
