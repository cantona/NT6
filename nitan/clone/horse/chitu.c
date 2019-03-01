inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(NOR + RED "赤兔馬" NOR, ({ "chitu ma"}));
        set("long", NOR + RED "渾身上下，火炭般赤，無半根雜毛；從頭至尾，長一丈；從蹄至項，高"
                              "八尺；嘶喊咆哮，有騰空入海之狀。\n"
                              "建安二十六年，關羽走麥城，兵敗遭擒，拒降，為孫權所害。其坐騎赤\n"
                              "兔馬為孫權賜予馬忠。赤兔馬絕食數日，不久即亡。\n" NOR);

        set("tili", 5000);
        set("max_tili", 5000);
        set("level", 4);

        set("can_go_any", 1);

        setup();
}
