// sword_book4.c

inherit ITEM;

void create()
{
        set_name("嵩山劍譜", ({ "sword book", "book" }));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
"當年五岳劍派與魔教十長老兩度會戰華山，五派好手死傷殆盡，五派
劍派的許多精世絕招，隨五派高手而逝。左冷禪會集本派殘存的耆宿，
將各人所記得的劍招，不論精粗，盡數錄了下來，匯成一部劍譜。這
數十年來，他去蕪存菁，將本派劍法中種種不夠狠辣的招數，不夠堂
皇的姿式，一一修改，使得本派劍法‘內八路，外九路’、一十七路
長短、快慢各路劍法完美無缺。
這本小冊子就是他整理的嵩山劍譜。\n");
                set("value", 1000);
                set("material", "paper");
                set("skill", ([
                        "name"        : "songshan-sword",
                        "exp_required": 10000,
                        "jing_cost"   : 20,
                        "difficulty"  : 20,
                        "max_skill"   : 120
                ]) );
        }
}