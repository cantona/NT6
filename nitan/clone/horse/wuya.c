inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(NOR + MAG "烏騅馬" NOR, ({ "wuzhui ma"}));
        set("long", NOR + MAG "此馬身高丈許，棕毛直立，通人性，雄麗無比。\n"
                              "烏騅是項羽的坐騎。一直跟隨他南征北戰，建立功勛無數。\n"
                              "項羽烏江自殺後，將愛馬烏騅送給了亭長。亭長帶着它過江，但是忠於主\n"
                              "人的烏騅自跳烏江而死。\n" NOR);

        set("tili", 3000);
        set("max_tili", 3000);
        set("level", 3);

        setup();
}
