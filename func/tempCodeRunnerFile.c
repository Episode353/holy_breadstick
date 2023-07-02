 // If it's not an item, check if it's a biome
                if (!isItem) {
                    for (int k = 0; k < numBiomes; k++) {
                        if (j >= biomes[k].start_x && j <= biomes[k].end_x &&
                            i >= biomes[k].start_y && i <= biomes[k].end_y) {
                            strcpy(color, biomes[k].color);
                            symbol = biomes[k].symbol;
                            break;
                        }
                    }
                }