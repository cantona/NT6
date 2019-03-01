//Edited by fandog, 02/15/2000
#include <ansi.h>
inherit ITEM;
int do_play(string arg);

//void setup()
//{}

void init()
{
        add_action("do_shan", "shan");
}

void create()
{
        set_name(HIW"羽毛扇"NOR, ({"yumaoshan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "這是一把洪湖羽毛扇。這種扇子選用各種鳥禽之翅、尾毛，按羽毛的色澤
紋理，制成扇面，然後配竹蔑、牛骨、象牙等作為扇骨，扇尾還吊一根絲
線結墜。民間又稱之為孔明扇。你可以扇扇(shan)它。\n");
                set("value", 300);
        }
//        setup();
}

int do_shan(string arg)
{
        if (!id(arg))
                return notify_fail("你要扇什麼？\n");
        switch( random(2) ) {
                case 0:
                        say(this_player()->name() + "拿起羽毛扇，悠閒自得地扇了扇，頗得孔明的遺風呢。\n");
                        write(this_player()->name() + "拿起羽毛扇，悠閒自得地扇了扇，頗得孔明的遺風呢。\n");

                        break;
                case 1:
                        say(this_player()->name() + "一邊搖著羽毛扇，一邊抑揚頓挫地吟著：羽扇綸巾，數千古風流人物，咱也算一個。\n");
                        write(this_player()->name() + "一邊搖著羽毛扇，一邊抑揚頓挫地吟著：羽扇綸巾，數千古風流人物，咱也算一個。\n");

                        break;
        }
        return 1;
}
