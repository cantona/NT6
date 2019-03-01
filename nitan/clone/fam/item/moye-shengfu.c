
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "莫邪聖符" NOR, ({ "moye fu", "moye", "fu" }) );
        set_weight(1);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "莫邪聖符可以將普通道具升級為自造道具，以後可以隨時召喚升級後的道具。\n"
                                                "指令格式： upd <欲升級道具ID> to <升級後的道具ID> \n"
                                                                "目前僅僅限于升級防具類道具。\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                        set("unit", "張");
        }

        setup();
}

// 檢查新ID是否合法
int check_legal_id(string id)
{
                int i;

                i = strlen(id);

                if ((strlen(id) < 4) || (strlen(id) > 10))
                {
                        write(WHT "\n對不起，升級後的ID必須是" HIY " 4 " NOR + WHT 
                                  "到" HIY " 10 " NOR + WHT "個英文字母。\n" NOR);
                        return 0;
                }

                while (i--)
        {
                        if (id[i] < 'a' || id[i] > 'z' )
                        {
                                write(WHT "\n對不起，你的英文名字只能用英文字母。\n" NOR);
                                return 0;
                        }
        }

                return 1;
}


void init()
{
        if (this_player() == environment())
        {
                add_action("do_upd", "upd");
        }
}


// 升級道具為自造兵器
// upd <目標道具ID> <升級後的ID>
int do_upd(string arg)
{
                object me;
                string tar_id, new_id, armor_type;
                object ob;
                mapping can_summon_list;
                string *key_can_summon_list;
                string head_file; // 自造物品文件開頭
                string input_file; // 最後寫入的文件信息
                mapping armor_prop, limit;
                string *key_armor_prop, *key_limit;
                int i;

                me = this_player();

                if (! arg)return notify_fail("指令格式: upd <欲升級道具ID> to <升級後的道具ID>\n");

                if (sscanf(arg, "%s to %s", tar_id, new_id) != 2)
                        return notify_fail("指令格式: upd <欲升級道具ID> to <升級後的道具ID>\n");
                
/*
1、首先判斷該道具是否存在。
2、該道具是否為防具。
3、該道具是否可升級
3.1 該道具是否下線不丟失
3.2 該道具是否為自造道具。
3.3 該物品新ID是否合法，全為英文名。
3.4 該物品新ID是否與現有自造物品ID重復（can_summon)。
*/
        // 首先判斷該道具是否存在
                if (! objectp(ob = present(tar_id, me)))
                        return notify_fail("你身上好象沒有這個物品吧！\n");

                // 檢查ob是否為防具
                if (! stringp(armor_type = ob->query("armor_type")))
                        return notify_fail("對不起，只能升級防具類物品。\n");

                // 該道具是否可升級
                // 該道具是否下線不丟失
                if (! ob->query_autoload())
                        return notify_fail("你只能升級下線不丟失的物品。\n");
                
                // 該道具是否為自造道具
                if (ob->is_item_make())
                        return notify_fail("自造物品不能升級。\n");                

                // 
                if (ob->query("no_upd"))
                        return notify_fail("該特殊物品不能升級。\n");
                        
                // 該物品新ID是否合法，全為英文名
                if (! check_legal_id(new_id))return 1;
                                                
                // 該物品新ID是否與現有自造物品ID重復（can_summon)
                can_summon_list = me->query("can_summon");

                if (mapp(can_summon_list))
                {
                        if (sizeof(can_summon_list))
                        {
                                key_can_summon_list = keys(can_summon_list);

                                if (member_array(new_id, key_can_summon_list) != -1)
                                {
                                        return notify_fail("升級後的ID名有重復，請輸入 summon 查看已有的ID名。\n");
                                }
                        }
                }
                
                // 如果是勛章則加上諸神賜予 xxx(id)
                if (ob->query("armor_type") == "medal" ||
                    ob->query("armor_type") == "medal2")
                {
                        ob->set("long", ob->query("long") + 
                                        HIC "只見勛章的邊緣刻著一排小字：諸神賜予 " + me->name() + HIC + "(" + me->query("id") + ")\n" NOR);
                }


/*
4、進行升級
4.1 根據道具類型設置相關數據，並寫入文件。
4.2 設置該玩家can_summon 數據。
4.3 destruct 該道具和升級道具，並提示summon
*/

                // 4、進行升級
                // 4.1 根據道具類型設置相關數據，並寫入文件。
                head_file = 
                "\n"
                "#include <ansi.h>\n"
                "#include <armor.h>\n"
                "\n"
                "inherit ==ARMOR_TYPE==;\n"
                "inherit F_ITEMMAKE;\n"
                "\n"
                "void create()\n"
                "{\n"
                "\tset_name(==ARMOR_NAME==, ({ ==ARMOR_ID== }));\n"
                "\tset_weight(==ARMOR_WEIGHT==);\n"
                "\tset(\"item_make\", 1);\n"
                "\tset(\"unit\", ==ARMOR_UNIT==);\n"
                "\tset(\"long\", ==ARMOR_LONG==);\n"
                "\tset(\"value\", ==ARMOR_VALUE==);\n"
                "\tset(\"point\", ==ARMOR_POINT==);\n"
                "\tset(\"material\", ==ARMOR_MATERIAL==);\n";
                if (ob->query("wear_msg"))
                {
                        head_file += "\tset(\"wear_msg\", \"" + ob->query("wear_msg") + "\");\n";
                }
                if (ob->query("remove_msg"))
                {
                        head_file += "\tset(\"remove_msg\", \"" + ob->query("remove_msg") + "\");\n";
                }
                head_file += "\tif (! check_clone()) return;\n";
                head_file += "\trestore();\n";

                // 替換head_file中內容
                // 1. ==ARMOR_TYPE== 防具類型
                //    ==ARMOR_ID==
                head_file = replace_string(head_file, "==ARMOR_TYPE==", upper_case(armor_type));
                head_file = replace_string(head_file, "==ARMOR_ID==", "\"" + new_id + "\"");
                // 2. ==ARMOR_NAME== 名稱
                head_file = replace_string(head_file, "==ARMOR_NAME==", "\"" + ob->name() + "\"");
                // 3. ==ARMOR_WEIGHT==
                head_file = replace_string(head_file, "==ARMOR_WEIGHT==", sprintf("%d", ob->query_weight()));
                // 4. ==ARMOR_UNIT==
                head_file = replace_string(head_file, "==ARMOR_UNIT==", "\"" + ob->query("unit") + "\"");
                // 5. ==ARMOR_LONG==
                head_file = replace_string(head_file, "==ARMOR_LONG==", "\"" + (ob->query("long") ? ob->query("long") : ob->query("name")) + "\\n\"");
                // 6. ==ARMOR_VALUE==
                head_file = replace_string(head_file, "==ARMOR_VALUE==", sprintf("%d", ob->query("value")));
                // 7. ==ARMOR_POINT==
                head_file = replace_string(head_file, "==ARMOR_POINT==", sprintf("%d", ob->query("armor_prop/armor") * 5 / 6));
                // 8. ==ARMOR_MATERIAL==
                head_file = replace_string(head_file, "==ARMOR_MATERIAL==", ob->query("material") ? 
                                                                            "\"" + ob->query("material") + "\"" : 
                                                                                "\"" +  "steel" + "\"");
                        
                // 11.設置道具的armor_pro
                armor_prop = ob->query("armor_prop");
                
                key_armor_prop = keys(armor_prop);
                input_file = head_file;
                if (sizeof(key_armor_prop))
                {                
                        for (i = 0; i < sizeof(key_armor_prop); i ++ )
                        {
                                if (key_armor_prop[i] == "armor")continue;                                
                                
                                // 如果為護身符 則暫時不寫入fy&qy值，在循環後單獨寫入
                                if (ob->query("armor_type") == "myheart" || 
                                    ob->query("armor_type") == "myheart2")
                                {
                                        if (key_armor_prop[i] =="fy" || key_armor_prop[i] == "qy")
                                                continue;
                                }

                                input_file += "\tset(\"armor_prop/" + key_armor_prop[i] + "\", ";
                                                                
                                if (stringp(armor_prop[key_armor_prop[i]]))
                                        input_file += armor_prop[key_armor_prop[i]] + ");\n";
                                else                                        
                                        input_file += sprintf("%d", armor_prop[key_armor_prop[i]]) + ");\n";
                        } 
                        
                        // 單獨寫入福緣及氣運的計算公式
                        if (ob->query("armor_type") == "myheart" || 
                            ob->query("armor_type") == "myheart2")
                        {
                                input_file += "\tset(\"armor_prop/fy" + "\", ";
                                input_file += sprintf("%d", ob->query("armor_prop/fy")) + " + f_enchase_points(0));\n";
                                input_file += "\tset(\"armor_prop/qy" + "\", ";
                                input_file += sprintf("%d", ob->query("armor_prop/qy")) + " + f_enchase_points(1));\n";                                
                        }
                
                }
                input_file += "\tset(\"armor_prop/armor\", apply_armor());\n";
                // 如果無armor_prop不能裝備，可設置
                input_file += "\tset(\"armor_prop/can_wear\", 1);\n";

                // 12. 設置道具limit信息
                limit = ob->query("limit");
                if (mapp(limit))key_limit = keys(limit);
                if (sizeof(key_limit))
                {
                        for (i = 0; i < sizeof(key_limit); i ++ )
                        {
                                input_file += "\tset(\"limit/" + key_limit[i] + "\", ";
                                input_file += sprintf("%d", limit[key_limit[i]]) + ");\n";
                        }                        
                }

                input_file += "\n\tsetup();\n";
                input_file += "}\n\n";
                input_file += "string long() { return query(\"long\") + item_long(); }\n\n";

                // 寫入文件
                if (! ITEM_D->extern_write_file("/data/item/" + me->query("id")[0..0] + "/" + me->query("id") + "-" + new_id + ".c",
                                              input_file, 
                                                                  1) )
                {
                        return notify_fail("升級失敗，寫入文件異常。\n");
                }                                

                // 更新道具
                load_object("/data/item/" + me->query("id")[0..0] + "/" + me->query("id") + "-" + new_id + ".c");

                // 記錄
                log_file("moyefu", me->query("id") + " 于 " + ctime(time()) + " 使用莫邪符升級 " + new_id + "。\n");
                
                // 設置CAN_SUMMON
                me->set("can_summon/" + new_id, "/data/item/" + me->query("id")[0..0] + "/" + me->query("id") + "-" + new_id + ".c");
                me->save();

                // 提示
                write(HIG "升級完畢，請輸入指令 summon " + new_id + " 召回升級後的物品。\n" NOR);

                destruct(ob);
                destruct(this_object());

                return 1;
}

int query_autoload()
{
         return 1;
}
