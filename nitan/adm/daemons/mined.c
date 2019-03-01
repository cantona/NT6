// mine_d.c

#define MINE_DIR        "/clone/mine/"

#include <mine_def.h>

string *valid_mine_classes = ({
        IRON_MINE,
});


int is_valid_mclass(string cs)
{
        if(!stringp(cs) || (member_array(cs, valid_mine_classes) == -1))
                return 0;

        return 1;
}

string chinese_mine_class(string cs)
{
        switch (cs)
        {
                case IRON_MINE:
                case IRON_RES_CU:
                        return "粗鐵";
                case IRON_RES_JING:
                        return "精鐵";
                case STEEL_RES:
                        return "鋼";
                case BLACK_IRON:
                        return "玄鐵";
                default:
                        return 0;
        }
}

int query_mine_class_value(string cs)
{
        switch (cs)
        {
                case IRON_RES_CU:
                        return 500;
                case IRON_RES_JING:
                        return 2000;
                case STEEL_RES:
                        return 7000;
                case BLACK_IRON:
                        return 10000;
                default:
                        return 0;
        }
}

object query_mine_class_up_ob(string cs)
{
        switch (cs)
        {
                case IRON_MINE:                // 鐵礦 -> 粗鐵
                        return new(MINE_DIR"iron_cu");
                case IRON_RES_CU:        // 粗鐵 -> 精鐵
                        return new(MINE_DIR"iron_jing");
                case IRON_RES_JING:        // 精鐵 -> 鋼
                        return new(MINE_DIR"iron_steel");
                case BLACK_IRON:
                        return new(MINE_DIR"black_iron");
                default:
                        return 0;
        }
}

int query_mine_class_up_quantity(string cs)
{
        switch (cs)
        {
                case IRON_RES_CU:        // 粗鐵 -> 精鐵
                        return 3;
                case IRON_RES_JING:        // 精鐵 -> 鋼
                        return 3;
                default:
                        return 0;
        }
}
