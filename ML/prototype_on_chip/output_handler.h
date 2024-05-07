/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef TENSORFLOW_LITE_BIRD_OUTPUT_HANDLER_H_
#define TENSORFLOW_LITE_BIRD_OUTPUT_HANDLER_H_

#include "tensorflow/lite/c/c_api_internal.h"
#include "tensorflow/lite/experimental/micro/micro_error_reporter.h"
#include <string>
#include <vector>

extern std::vector<std::string> birdVector = {
    "Acadian_Flycatcher", "American_Crow", "American_Goldfinch", "American_Pipit", "American_Redstart",
    "American_Three_toed_Woodpecker", "Anna_Hummingbird", "Arctic_Tern", "Baird_Sparrow", "Baltimore_Oriole",
    "Bank_Swallow", "Barn_Swallow", "Bay_breasted_Warbler", "Belted_Kingfisher", "Bewick_Wren", "Black_Tern",
    "Black_and_white_Warbler", "Black_billed_Cuckoo", "Black_capped_Vireo", "Black_footed_Albatross",
    "Black_throated_Blue_Warbler", "Black_throated_Sparrow", "Blue_Grosbeak", "Blue_Jay", "Blue_headed_Vireo",
    "Blue_winged_Warbler", "Boat_tailed_Grackle", "Bobolink", "Bohemian_Waxwing", "Brandt_Cormorant",
    "Brewer_Blackbird", "Brewer_Sparrow", "Bronzed_Cowbird", "Brown_Creeper", "Brown_Pelican", "Brown_Thrasher",
    "Cactus_Wren", "California_Gull", "Canada_Warbler", "Cape_Glossy_Starling", "Cape_May_Warbler", "Cardinal",
    "Carolina_Wren", "Caspian_Tern", "Cedar_Waxwing", "Cerulean_Warbler", "Chestnut_sided_Warbler",
    "Chipping_Sparrow", "Chuck_will_Widow", "Clark_Nutcracker", "Clay_colored_Sparrow", "Cliff_Swallow",
    "Common_Raven", "Common_Tern", "Common_Yellowthroat", "Crested_Auklet", "Dark_eyed_Junco", "Downy_Woodpecker",
    "Eared_Grebe", "Eastern_Towhee", "Elegant_Tern", "European_Goldfinch", "Evening_Grosbeak", "Field_Sparrow",
    "Fish_Crow", "Florida_Jay", "Forsters_Tern", "Fox_Sparrow", "Frigatebird", "Gadwall", "Geococcyx",
    "Glaucous_winged_Gull", "Golden_winged_Warbler", "Grasshopper_Sparrow", "Gray_Catbird", "Gray_Kingbird",
    "Gray_crowned_Rosy_Finch", "Great_Crested_Flycatcher", "Great_Grey_Shrike", "Green_Jay", "Green_Kingfisher",
    "Green_Violetear", "Green_tailed_Towhee", "Groove_billed_Ani", "Harris_Sparrow", "Heermann_Gull",
    "Henslow_Sparrow", "Herring_Gull", "Hooded_Merganser", "Hooded_Oriole", "Hooded_Warbler", "Horned_Grebe",
    "Horned_Lark", "Horned_Puffin", "House_Sparrow", "House_Wren", "Indigo_Bunting", "Ivory_Gull",
    "Kentucky_Warbler", "Laysan_Albatross", "Lazuli_Bunting", "Le_Conte_Sparrow", "Least_Auklet",
    "Least_Flycatcher", "Least_Tern", "Lincoln_Sparrow", "Loggerhead_Shrike", "Long_tailed_Jaeger",
    "Louisiana_Waterthrush", "Magnolia_Warbler", "Mallard", "Mangrove_Cuckoo", "Marsh_Wren", "Mockingbird",
    "Mourning_Warbler", "Myrtle_Warbler", "Nashville_Warbler", "Nelson_Sharp_tailed_Sparrow", "Nighthawk",
    "Northern_Flicker", "Northern_Fulmar", "Northern_Waterthrush", "Olive_sided_Flycatcher",
    "Orange_crowned_Warbler", "Orchard_Oriole", "Ovenbird", "Pacific_Loon", "Painted_Bunting", "Palm_Warbler",
    "Parakeet_Auklet", "Pelagic_Cormorant", "Philadelphia_Vireo", "Pied_Kingfisher", "Pied_billed_Grebe",
    "Pigeon_Guillemot", "Pileated_Woodpecker", "Pine_Grosbeak", "Pine_Warbler", "Pomarine_Jaeger", "Prairie_Warbler",
    "Prothonotary_Warbler", "Purple_Finch", "Red_bellied_Woodpecker", "Red_breasted_Merganser",
    "Red_cockaded_Woodpecker", "Red_eyed_Vireo", "Red_faced_Cormorant", "Red_headed_Woodpecker",
    "Red_legged_Kittiwake", "Red_winged_Blackbird", "Rhinoceros_Auklet", "Ring_billed_Gull", "Ringed_Kingfisher",
    "Rock_Wren", "Rose_breasted_Grosbeak", "Ruby_throated_Hummingbird", "Rufous_Hummingbird", "Rusty_Blackbird",
    "Sage_Thrasher", "Savannah_Sparrow", "Sayornis", "Scarlet_Tanager", "Scissor_tailed_Flycatcher", "Scott_Oriole",
    "Seaside_Sparrow", "Shiny_Cowbird", "Slaty_backed_Gull", "Song_Sparrow", "Sooty_Albatross", "Spotted_Catbird",
    "Summer_Tanager", "Swainson_Warbler", "Tennessee_Warbler", "Tree_Sparrow", "Tree_Swallow", "Tropical_Kingbird",
    "Vermilion_Flycatcher", "Vesper_Sparrow", "Warbling_Vireo", "Western_Grebe", "Western_Gull", "Western_Meadowlark",
    "Western_Wood_Pewee", "Whip_poor_Will", "White_Pelican", "White_breasted_Kingfisher", "White_breasted_Nuthatch",
    "White_crowned_Sparrow", "White_eyed_Vireo", "White_necked_Raven", "White_throated_Sparrow", "Wilson_Warbler",
    "Winter_Wren", "Worm_eating_Warbler", "Yellow_Warbler", "Yellow_bellied_Flycatcher", "Yellow_billed_Cuckoo",
    "Yellow_breasted_Chat", "Yellow_headed_Blackbird", "Yellow_throated_Vireo"
};


void HandleOutput(tflite::ErrorReporter* error_reporter, int kind);


#endif  // TENSORFLOW_LITE_BIRD_OUTPUT_HANDLER_H_
