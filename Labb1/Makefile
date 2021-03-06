CC = /home/labuser/devkitARM/bin/arm-eabi-gcc
LD = /home/labuser/devkitARM/bin/arm-eabi-gcc
OBJCOPY = /home/labuser/devkitARM/bin/arm-eabi-objcopy

SERIALPORT = /dev/ttyUSB0

DEFINES = 

LIBS = 

SOURCE_DIR = .
BUILD_DIR = Build

C_OPTS =	-std=c99 \
			-O3 \
			-Wall \
			-Werror \
			-mcpu=cortex-a8 \
			-g3 \
			-gdwarf-2

MAIN_C_FILES =	LFO.c \
				Main.c \
				Phaser.c

TEST_C_FILES =	Test.c \
				CT2.c

COMMON_C_FILES =	Audio.c \
					Background.c \
					DisplayDOGM128.c \
					Encoders.c \
					Graphics.c \
					I2C.c \
					Interrupts.c \
					Leds.c \
					Serial.c \
					Utils.c

S_FILES =	InterruptHandler.S \
			Startup.S

MAIN_OBJS = $(MAIN_C_FILES:%.c=$(BUILD_DIR)/%.o)

TEST_OBJS = $(TEST_C_FILES:%.c=$(BUILD_DIR)/%.o)

COMMON_OBJS = $(COMMON_C_FILES:%.c=$(BUILD_DIR)/%.o)

S_OBJS = $(S_FILES:%.S=$(BUILD_DIR)/%.o)

ALL_OBJS = $(MAIN_OBJS) $(TEST_OBJS) $(COMMON_OBJS) $(S_OBJS)

ALL_CFLAGS = $(C_OPTS) $(DEFINES) $(CFLAGS)
ALL_LDFLAGS =	$(LD_FLAGS) \
				-nostartfiles \
				-Wl,-T,Linker.ld \
				-mcpu=cortex-a8 \
				-g3 \
				-gdwarf-2

AUTODEPENDENCY_CFLAGS=-MMD -MF$(@:.o=.d) -MT$@




all: Labb1.bin

clean:
	rm -rf $(BUILD_DIR) Labb1.elf Labb1.bin Test.elf Test.bin

upload: Labb1.bin
	stty -F $(SERIALPORT) ispeed 115200 ospeed 115200 -crtscts -ixon
	expect \
	-c 'set timeout -1' \
	-c 'spawn cu -l $(SERIALPORT) -s 115200' \
	-c 'expect "beagleboard.org #"' \
	-c 'sleep 0.1' \
	-c 'send "loady 0x80300000\r"' \
	-c 'sleep 0.1'
	sz --ymodem $^ <$(SERIALPORT) >$(SERIALPORT)
	expect \
	-c 'set timeout -1' \
	-c 'spawn cu -l $(SERIALPORT) -s 115200' \
	-c 'send "\r"' \
	-c 'expect "beagleboard.org #"' \
	-c 'sleep 0.1' \
	-c 'send "go 0x80300000\r"' \
	-c 'sleep 0.1'

test: Test.bin
	stty -F $(SERIALPORT) ispeed 115200 ospeed 115200 -crtscts
	expect \
	-c 'set timeout -1' \
	-c 'spawn cu -l $(SERIALPORT) -s 115200' \
	-c 'expect "beagleboard.org #"' \
	-c 'sleep 0.1' \
	-c 'send "loady 0x80300000\r"' \
	-c 'sleep 0.1'
	sz --ymodem $^ <$(SERIALPORT) >$(SERIALPORT)
	expect \
	-c 'set timeout -1' \
	-c 'spawn cu -l $(SERIALPORT) -s 115200' \
	-c 'send "\r"' \
	-c 'expect "beagleboard.org #"' \
	-c 'sleep 0.1' \
	-c 'send "go 0x80300000\r"' \
	-c 'sleep 0.1'

doxygen: Documentation/doxygen.conf
	doxygen $^

Labb1.bin: Labb1.elf
	$(OBJCOPY) -O binary $^ $@

Labb1.elf: $(MAIN_OBJS) $(COMMON_OBJS) $(S_OBJS)
	$(LD) $(ALL_LDFLAGS) -o $@ $^ $(LIBS)

Test.bin: Test.elf
	$(OBJCOPY) -O binary $^ $@

Test.elf: $(TEST_OBJS) $(COMMON_OBJS) $(S_OBJS)
	$(LD) $(ALL_LDFLAGS) -o $@ $^ $(LIBS)

#Background.c: Material/Background.png Material/PNGToC.pl
#	perl Material/PNGToC.pl Material/Background.png background >Background.c

.SUFFIXES: .o .c .S

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(ALL_CFLAGS) $(AUTODEPENDENCY_CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.S
	@mkdir -p $(dir $@)
	$(CC) $(ALL_CFLAGS) $(AUTODEPENDENCY_CFLAGS) -c $< -o $@

.PHONY: clean upload test doxygen

-include $(ALL_OBJS:.o=.d)

