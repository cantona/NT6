#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIR "【昊天塔內】" NOR);
        set("long", HIR @LONG

              昊     天     塔      內

    這裏是昊天塔內，四周無任何出口，但見塔壁光彩耀眼，
似乎藴藏着極大的力量。

LONG NOR );

        set("sky", 1);
        setup();
}

void init()
{     
       string msg = HIM "塔內放射出耀眼的光芒，令你無法睜開雙眼 ……\n" NOR;
       
       msg += HIG "數道光芒將你團團圍住，似乎要鑽入你的七竅之內 ……\n" NOR;
       msg += HIY "慢慢地你覺得自己漸漸地與肢體分離，意識也漸漸模糊 ……\n" NOR;
       msg += HIR "正當你快要失去知覺的時候，七彩光芒將你卷出了昊天塔 ……\n" NOR;
       msg += HIW "你感覺你在時空中穿梭許久，渾身無法動彈，意識也在逐漸模糊，\n"
                  "漸漸地，你再也想不起自己身在何處，為何會來到這裏，自己又\n"
                  "是誰，將要到何方 ……\n\n" NOR;

       tell_object(this_object(), msg);
       return;
}
