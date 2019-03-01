#include <ansi.h>
inherit ITEM;

string long();

void create()
{
        set_name(NOR + WHT "刺青圖" NOR, ({ "tattoo paper", "tattoo", "paper" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張古舊的圖片，上面繪著些紋樣。");
                set("unit", "張");
                set("material", "paper");
                set("value", 500);                        // 刺青時的花費與圖騰的價值相關
                set("tattoo_long", "精忠報國四個大字");   // 刺青後該部位的描述
                set("can_tattoo", ({ "臉部", "胸口",
                                     "後背", "左臂",
                                     "右臂", "臀部", })); // 身體能夠接受刺青的部位
                set("tattoo_type", ({ "膂力", "悟性",     // 增加後天屬性的種類，這項屬性
                                      "根骨", "身法",     // 的目的僅是讓玩家能夠看到。
                                      "容貌", }));
                set("tattoo_str", 1);                     // 對應上面的後天屬性種類，增加
                set("tattoo_int", 1);                     // 相應的記號。
                set("tattoo_con", 1);
                set("tattoo_dex", 1);
                set("tattoo_per", 1);
                set("tattoo_special", "power");           // 刺青時增加的特殊技能
                set("tattoo_spcname", "天神降世");        // 在look時所提供的提示信息
        }
}

string long()
{
        string msg;

        if (query("can_tattoo"))
        {
                msg = WHT "這是一張" + name() + NOR + WHT "，圖中描著" + query("tattoo_long") + "。你可以"
                      "讓紋身師傅參照著圖樣在你的" + implode(query("can_tattoo"),
                      "、") + "上刺青，以提高你的" + implode(query("tattoo_type"),
                      "、") + "。";

                if (query("tattoo_special"))
                {
                        msg += "此外，" + name() + NOR + WHT "還能帶"
                               "給你" + query("tattoo_spcname") + NOR
                               WHT "的神秘力量。";
                } else
                {
                        msg += "此外，" + name() + NOR + WHT "似乎還"
                               "蘊藏著某些未知的神秘力量。";
                }
        } else
                msg = "這是一張古舊的圖片，上面繪著些紋樣。";

        return sort_string(msg, 54);
}

int query_autoload()
{
        return 1;
}
