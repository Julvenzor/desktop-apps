PWD := $(shell pwd)

COMPANY_NAME ?= ONLYOFFICE
PRODUCT_NAME ?= Desktop Editors
PRODUCT_NAME_SHORT ?= $(subst $(empty) $(empty),,$(PRODUCT_NAME))

COMPANY_NAME_LOW = $(shell echo $(COMPANY_NAME) | tr A-Z a-z)
PRODUCT_NAME_LOW = $(shell echo $(PRODUCT_NAME_SHORT) | tr A-Z a-z)

PUBLISHER_NAME ?= Ascensio System SIA
PUBLISHER_URL ?= http://onlyoffice.com
SUPPORT_URL ?= http://support.onlyoffice.com
SUPPORT_MAIL ?= support@onlyoffice.com

PRODUCT_VERSION ?= 0.0.0
BUILD_NUMBER ?= 0
PACKAGE_EDITION ?= cool

BRANDING_DIR ?= $(PWD)/branding

ifeq ($(COMPANY_NAME), ONLYOFFICE)
	PACKAGE_NAME := $(COMPANY_NAME_LOW)-$(PRODUCT_NAME_LOW)
else
	PACKAGE_NAME := $(COMPANY_NAME_LOW)
endif
PACKAGE_VERSION := $(PRODUCT_VERSION)-$(BUILD_NUMBER)

UNAME_M ?= $(shell uname -m)
ifeq ($(UNAME_M),x86_64)
	RPM_ARCH = x86_64
	DEB_ARCH = amd64
	TAR_ARCH = x86_64
	URPMI_ARCH = x86_64
	APT_RPM_ARCH = x86_64
	ARCHITECTURE = 64
endif
ifneq ($(filter %86,$(UNAME_M)),)
	RPM_ARCH = i686
	DEB_ARCH = i386
	URPMI_ARCH = i586
	APT_RPM_ARCH = i586
	TAR_ARCH = x86
	ARCHITECTURE = 32
endif
ifneq ($(filter aarch%,$(UNAME_M)),)
	RPM_ARCH = aarch64
	DEB_ARCH = arm64
	URPMI_ARCH = aarch64
	APT_RPM_ARCH = aarch64
	TAR_ARCH = aarch64
	ARCHITECTURE = arm64
endif

RPM_BUILD_DIR = $(PWD)/rpm/builddir
APT_RPM_BUILD_DIR = $(PWD)/apt-rpm/builddir
URPMI_BUILD_DIR = $(PWD)/urpmi/builddir
SUSE_RPM_BUILD_DIR = $(PWD)/suse-rpm/builddir
TAR_BUILD_DIR = $(PWD)/tar

RPM_PACKAGE_DIR = $(RPM_BUILD_DIR)/RPMS/$(RPM_ARCH)
APT_RPM_PACKAGE_DIR = $(APT_RPM_BUILD_DIR)/RPMS/$(APT_RPM_ARCH)
URPMI_PACKAGE_DIR = $(URPMI_BUILD_DIR)/RPMS/$(URPMI_ARCH)
SUSE_RPM_PACKAGE_DIR = $(SUSE_RPM_BUILD_DIR)/RPMS/$(RPM_ARCH)
TAR_PACKAGE_DIR = $(TAR_BUILD_DIR)

DISTRIB_CODENAME=$(shell lsb_release -cs || echo "n/a")
ifeq ($(DISTRIB_CODENAME),trusty)
  RPM_RELEASE      := el7
  APT_RPM_RELEASE  := p7
  URPMI_RELEASE    := r6
  SUSE_RPM_RELEASE := suse12
  DEB_RELEASE      := jessie
  TAR_RELEASE      := gcc4
else ifeq ($(DISTRIB_CODENAME),xenial)
  RPM_RELEASE      := el8
  APT_RPM_RELEASE  := p8
  URPMI_RELEASE    := r9
  SUSE_RPM_RELEASE := suse15
  DEB_RELEASE      := stretch
  TAR_RELEASE      := gcc5
endif
DEB_ASTRA_RELEASE  := astra-signed

RPM = $(RPM_PACKAGE_DIR)/$(PACKAGE_NAME)-$(PACKAGE_VERSION)$(RPM_RELEASE:%=.%).$(RPM_ARCH).rpm
APT_RPM = $(APT_RPM_PACKAGE_DIR)/$(PACKAGE_NAME)-$(PACKAGE_VERSION)$(APT_RPM_RELEASE:%=.%).$(APT_RPM_ARCH).rpm
URPMI = $(URPMI_PACKAGE_DIR)/$(PACKAGE_NAME)-$(PACKAGE_VERSION)$(URPMI_RELEASE:%=.%).$(URPMI_ARCH).rpm
SUSE_RPM = $(SUSE_RPM_PACKAGE_DIR)/$(PACKAGE_NAME)-$(PACKAGE_VERSION)$(SUSE_RPM_RELEASE:%=.%).$(RPM_ARCH).rpm
DEB = deb/$(PACKAGE_NAME)_$(PACKAGE_VERSION)$(DEB_RELEASE:%=~%)_$(DEB_ARCH).deb
DEB_ASTRA = deb-astra/$(PACKAGE_NAME)_$(PACKAGE_VERSION)$(DEB_ASTRA_RELEASE:%=~%)_$(DEB_ARCH).deb
TAR = $(TAR_PACKAGE_DIR)/$(PACKAGE_NAME)-$(PACKAGE_VERSION)$(TAR_RELEASE:%=_%)-$(TAR_ARCH).tar.gz
HELP_TAR = $(TAR_PACKAGE_DIR)/$(PACKAGE_NAME)-help-$(PACKAGE_VERSION)$(TAR_RELEASE:%=_%)-any.tar.xz

ifeq ($(COMPANY_NAME), ONLYOFFICE)
	DESKTOPEDITORS_PREFIX := $(COMPANY_NAME_LOW)/$(PRODUCT_NAME_LOW)
	DESKTOPEDITORS_EXEC := $(PACKAGE_NAME)
else
	DESKTOPEDITORS_PREFIX := $(COMPANY_NAME_LOW)/desktopeditors
	MEDIAVIEWER_PREFIX := $(COMPANY_NAME_LOW)/mediaviewer
	DESKTOPEDITORS_EXEC := $(COMPANY_NAME_LOW)-desktopeditors
	IMAGEVIEWER_EXEC := $(COMPANY_NAME_LOW)-imageviewer
	VIDEOPLAYER_EXEC := $(COMPANY_NAME_LOW)-videoplayer
endif

LINUX_DEPS += common/usr/share/applications/variables.m4
BIN_FILES += common/usr/bin/$(DESKTOPEDITORS_EXEC)
DESKTOP_FILES += common/usr/share/applications/$(DESKTOPEDITORS_EXEC).desktop
ifeq ($(COMPANY_NAME), ONLYOFFICE)
	SYMLINK += common/usr/bin/desktopeditors
else
	BIN_FILES += common/usr/bin/$(IMAGEVIEWER_EXEC)
	BIN_FILES += common/usr/bin/$(VIDEOPLAYER_EXEC)
	DESKTOP_FILES += common/usr/share/applications/$(IMAGEVIEWER_EXEC).desktop
	DESKTOP_FILES += common/usr/share/applications/$(VIDEOPLAYER_EXEC).desktop
	SYMLINK += common/usr/bin/$(COMPANY_NAME_LOW)
	DEB_DEPS += common/usr/share/flyfm/templates/desktopeditors.docx.desktop
	DEB_DEPS += common/usr/share/flyfm/templates/desktopeditors.xlsx.desktop
	DEB_DEPS += common/usr/share/flyfm/templates/desktopeditors.pptx.desktop
endif
LINUX_DEPS += $(BIN_FILES)
LINUX_DEPS += $(DESKTOP_FILES)
LINUX_DEPS += $(SYMLINK)

DEB_DEPS += deb/build/debian/changelog
DEB_DEPS += deb/build/debian/compat
DEB_DEPS += deb/build/debian/control
DEB_DEPS += deb/build/debian/postinst
DEB_DEPS += deb/build/debian/postrm
DEB_DEPS += deb/build/debian/prerm
DEB_DEPS += deb/build/debian/rules
DEB_DEPS += deb/build/debian/source/format
DEB_DEPS += deb/build/debian/$(PACKAGE_NAME).dirs
DEB_DEPS += deb/build/debian/$(PACKAGE_NAME).install
DEB_DEPS += deb/build/debian/$(PACKAGE_NAME).links
DEB_DEPS += deb/build/debian/$(PACKAGE_NAME)-help.install

DEB_ASTRA_DEPS += deb-astra/build/debian/changelog
DEB_ASTRA_DEPS += deb-astra/build/debian/compat
DEB_ASTRA_DEPS += deb-astra/build/debian/control
DEB_ASTRA_DEPS += deb-astra/build/debian/postinst
DEB_ASTRA_DEPS += deb-astra/build/debian/postrm
DEB_ASTRA_DEPS += deb-astra/build/debian/prerm
DEB_ASTRA_DEPS += deb-astra/build/debian/rules
DEB_ASTRA_DEPS += deb-astra/build/debian/source/format
DEB_ASTRA_DEPS += deb-astra/build/debian/$(PACKAGE_NAME).dirs
DEB_ASTRA_DEPS += deb-astra/build/debian/$(PACKAGE_NAME).install
DEB_ASTRA_DEPS += deb-astra/build/debian/$(PACKAGE_NAME).links
DEB_ASTRA_DEPS += common/usr/share/flyfm/templates/desktopeditors.docx.desktop
DEB_ASTRA_DEPS += common/usr/share/flyfm/templates/desktopeditors.xlsx.desktop
DEB_ASTRA_DEPS += common/usr/share/flyfm/templates/desktopeditors.pptx.desktop

INSTALLER_DEPENDENCY += desktopeditor

USR_LIB_X64 := /usr/lib/x86_64-linux-gnu

SRC += ../../../../build_tools/out/linux_$(ARCHITECTURE)/$(DESKTOPEDITORS_PREFIX)
HELP_SRC = ../../../../build_tools/out/linux_$(ARCHITECTURE)/$(DESKTOPEDITORS_PREFIX)-help
ifneq ($(COMPANY_NAME), ONLYOFFICE)
	SRC += ../../../../build_tools/out/linux_$(ARCHITECTURE)/$(MEDIAVIEWER_PREFIX)
endif


INSTALLER := qt-installer/$(PACKAGE_NAME)-installer-$(TAR_ARCH)
#QT_LIBS := $(shell qmake -query QT_INSTALL_LIBS)
#QT_PLUGINS := $(shell qmake -query QT_INSTALL_PLUGINS)

PLATFORM := linux_64_static_stdlib

M4_PARAMS += -D M4_COMPANY_NAME='$(COMPANY_NAME)'
M4_PARAMS += -D M4_PRODUCT_NAME='$(PRODUCT_NAME)'
M4_PARAMS += -D M4_PUBLISHER_NAME='$(PUBLISHER_NAME)'
M4_PARAMS += -D M4_PUBLISHER_URL='$(PUBLISHER_URL)'
M4_PARAMS += -D M4_SUPPORT_MAIL='$(SUPPORT_MAIL)'
M4_PARAMS += -D M4_SUPPORT_URL='$(SUPPORT_URL)'
M4_PARAMS += -D M4_PACKAGE_NAME='$(PACKAGE_NAME)'
M4_PARAMS += -D M4_PACKAGE_EDITION='$(PACKAGE_EDITION)'
M4_PARAMS += -D M4_DESKTOPEDITORS_PREFIX='$(DESKTOPEDITORS_PREFIX)'
M4_PARAMS += -D M4_DESKTOPEDITORS_EXEC='$(DESKTOPEDITORS_EXEC)'
ifneq ($(COMPANY_NAME), ONLYOFFICE)
	M4_PARAMS += -D M4_MEDIAVIEWER_PREFIX='$(MEDIAVIEWER_PREFIX)'
	M4_PARAMS += -D M4_IMAGEVIEWER_EXEC='$(IMAGEVIEWER_EXEC)'
	M4_PARAMS += -D M4_VIDEOPLAYER_EXEC='$(VIDEOPLAYER_EXEC)'
	M4_PARAMS += -D M4_SCHEME_HANDLER='$(COMPANY_NAME_LOW)'
else
	M4_PARAMS += -D M4_SCHEME_HANDLER='oo-office'
endif
M4_PARAMS += -D M4_DEB_ARCH='$(DEB_ARCH)'
M4_DEB_PARAMS = $(M4_PARAMS)
M4_DEB_PARAMS += -D M4_PACKAGE_VERSION='$(PACKAGE_VERSION)$(DEB_RELEASE:%=~%)'
M4_DEB_ASTRA_PARAMS = $(M4_PARAMS)
M4_DEB_ASTRA_PARAMS += -D M4_ASTRALINUX_KEYS_DIR='$(abspath $(ASTRALINUX_KEYS_DIR))'
M4_DEB_ASTRA_PARAMS += -D M4_ASTRALINUX_SIGN_IMAGE='$(ASTRALINUX_SIGN_IMAGE)'
M4_DEB_ASTRA_PARAMS += -D M4_PACKAGE_VERSION='$(PACKAGE_VERSION)$(DEB_ASTRA_RELEASE:%=~%)'

RPM_PARAMS += --define '_company_name $(COMPANY_NAME)'
RPM_PARAMS += --define '_product_name $(PRODUCT_NAME)'
RPM_PARAMS += --define '_publisher_name $(PUBLISHER_NAME)'
RPM_PARAMS += --define '_publisher_url $(PUBLISHER_URL)'
RPM_PARAMS += --define '_support_mail $(SUPPORT_MAIL)'
RPM_PARAMS += --define '_package_name $(PACKAGE_NAME)'
RPM_PARAMS += --define '_package_edition $(PACKAGE_EDITION)'
RPM_PARAMS += --define '_product_version $(PRODUCT_VERSION)'
RPM_PARAMS += --define '_desktopeditors_prefix $(DESKTOPEDITORS_PREFIX)'
RPM_PARAMS += --define '_desktopeditors_exec $(DESKTOPEDITORS_EXEC)'
ifneq ($(COMPANY_NAME), ONLYOFFICE)
	RPM_PARAMS += --define '_mediaviewer_prefix $(MEDIAVIEWER_PREFIX)'
	RPM_PARAMS += --define '_imageviewer_exec $(IMAGEVIEWER_EXEC)'
	RPM_PARAMS += --define '_videoplayer_exec $(VIDEOPLAYER_EXEC)'
	RPM_PARAMS += --define '_scheme_handler $(COMPANY_NAME_LOW)'
else
	RPM_PARAMS += --define '_scheme_handler oo-office'
endif
RPM_PARAMS += --define '_binary_payload w7.xzdio'

.PHONY: all clean branding packages rpm deb deb-astra apt-rpm suse-rpm tar desktopeditor qt-redist libstdc++-addon libc-addon

all: rpm deb apt-rpm urpmi suse-rpm tar
#installer

rpm: $(RPM)

deb: $(DEB)

deb-astra: $(DEB_ASTRA)

tar: $(TAR) $(HELP_TAR)

apt-rpm: $(APT_RPM)

urpmi: $(URPMI)

suse-rpm: $(SUSE_RPM)

rpm_aarch64 : ARCHITECTURE = arm64
rpm_aarch64 : RPM_ARCH = aarch64
rpm_aarch64 : $(RPM)

installer: $(INSTALLER)

PACKAGES += $(DEB) $(RPM) $(APT_RPM) $(URPMI) $(SUSE_RPM) $(TAR) $(HELP_TAR)
ifneq ($(COMPANY_NAME), ONLYOFFICE)
PACKAGES += $(DEB_ASTRA)
endif

packages: $(PACKAGES)

clean:
	rm -rfv \
		common/etc \
		common/opt \
		common/help \
		$(LINUX_DEPS) \
		deb/build \
		deb/*.buildinfo \
		deb/*.changes \
		deb/*.ddeb \
		deb/*.deb \
		deb-astra \
		$(RPM_BUILD_DIR) \
		$(APT_RPM_BUILD_DIR) \
		$(URPMI_BUILD_DIR) \
		$(SUSE_RPM_BUILD_DIR) \
		$(TAR_BUILD_DIR) \
		rpm/$(PACKAGE_NAME).spec \
		apt-rpm/$(PACKAGE_NAME).spec \
		urpmi/$(PACKAGE_NAME).spec \
		suse-rpm/$(PACKAGE_NAME).spec \
		$(INSTALLER)\
		*.tar.gz

branding: $(BRANDING_DIR)
	cp -rf $(BRANDING_DIR)/* $(PWD)/

desktopeditor: branding $(LINUX_DEPS)
	mkdir -p common/opt
	cp -rft common/opt $(SRC)

	cp -rf ../../../common/package/license/agpl-3.0.htm common/opt/desktopeditors/LICENSE.htm
	cp -rf ../../../common/package/license/3dparty/3DPARTYLICENSE common/opt/desktopeditors

	cp -rf ../../../common/package/mimetypes common/opt/desktopeditors

	chmod 755 common/opt/desktopeditors/DesktopEditors
ifneq ($(COMPANY_NAME), ONLYOFFICE)
	chmod 755 common/opt/mediaviewer/ImageViewer
	chmod 755 common/opt/mediaviewer/VideoPlayer
endif
	mkdir -p common/help
	cp -rf $(HELP_SRC)/. common/help/desktopeditors

qt-redist:
	cp -r -L -t common/opt/desktopeditors/ \
		$(QT_PLUGINS)/bearer \
		$(QT_PLUGINS)/imageformats \
		$(QT_PLUGINS)/platforms \
		$(QT_PLUGINS)/platformthemes \
		$(QT_PLUGINS)/printsupport \
		$(QT_LIBS)/libQt5Core.so.5 \
		$(QT_LIBS)/libQt5DBus.so.5 \
		$(QT_LIBS)/libQt5Gui.so.5 \
		$(QT_LIBS)/libQt5PrintSupport.so.5 \
		$(QT_LIBS)/libQt5Widgets.so.5 \
		$(QT_LIBS)/libQt5X11Extras.so.5 \
		$(QT_LIBS)/libQt5XcbQpa.so.5
		# $(USR_LIB_X64)/libicudata.so.52 \
		# $(USR_LIB_X64)/libicui18n.so.52 \
		# $(USR_LIB_X64)/libicuuc.so.52

$(RPM): desktopeditor rpm/$(PACKAGE_NAME).spec
	cd rpm && rpmbuild -bb \
		--define "_topdir $(RPM_BUILD_DIR)" \
		--define "_build_number $(BUILD_NUMBER)$(RPM_RELEASE:%=.%)" \
		--define "_package_arch $(RPM_ARCH)" \
		--target $(RPM_ARCH) \
		$(RPM_PARAMS) \
		package.spec

deb/build/debian/% : deb/template/%
	mkdir -pv $(@D) && cp -fv $< $@

deb/build/debian/% : deb/template/%.m4
	mkdir -pv $(@D) && m4 $(M4_DEB_PARAMS) $< > $@

deb/build/debian/$(PACKAGE_NAME).% : deb/template/package.%.m4
	mkdir -pv $(@D) && m4 $(M4_DEB_PARAMS) $< > $@

deb/build/debian/$(PACKAGE_NAME)-help.% : deb/template/package-help.%.m4
	mkdir -pv $(@D) && m4 $(M4_DEB_PARAMS) $< > $@

deb-astra/build/debian/% : deb/template/%
	mkdir -pv $(@D) && cp -fv $< $@

deb-astra/build/debian/% : deb/template/%.m4
	mkdir -pv $(@D) && \
	m4 $(M4_DEB_ASTRA_PARAMS) $< > $@

deb-astra/build/debian/$(PACKAGE_NAME).% : deb/template/package.%.m4
	mkdir -pv $(@D) && \
	m4 $(M4_DEB_ASTRA_PARAMS) $< > $@

$(DEB): desktopeditor $(DEB_DEPS)
	cd deb/build && dpkg-buildpackage -b -uc -us

$(DEB_ASTRA): desktopeditor $(DEB_ASTRA_DEPS)
	cd deb-astra/build && dpkg-buildpackage -b -uc -us

$(APT_RPM): desktopeditor apt-rpm/$(PACKAGE_NAME).spec
	cd apt-rpm && setarch $(APT_RPM_ARCH) rpmbuild -bb \
		--define "_topdir $(APT_RPM_BUILD_DIR)" \
		--define "_build_number $(BUILD_NUMBER)$(APT_RPM_RELEASE:%=.%)" \
		--define "_package_arch $(APT_RPM_ARCH)" \
		--target $(RPM_ARCH) \
		$(RPM_PARAMS) \
		package.spec

$(URPMI): desktopeditor urpmi/$(PACKAGE_NAME).spec
	cd urpmi && setarch $(URPMI_ARCH) rpmbuild -bb \
		--define "_topdir $(URPMI_BUILD_DIR)" \
		--define "_build_number $(BUILD_NUMBER)$(URPMI_RELEASE:%=.%)" \
		--define "_package_arch $(URPMI_ARCH)" \
		--target $(RPM_ARCH) \
		$(RPM_PARAMS) \
		package.spec

$(SUSE_RPM): desktopeditor suse-rpm/$(PACKAGE_NAME).spec
	cd suse-rpm && rpmbuild -bb \
		--define "_topdir $(SUSE_RPM_BUILD_DIR)" \
		--define "_build_number $(BUILD_NUMBER)$(SUSE_RPM_RELEASE:%=.%)" \
		--define "_package_arch $(RPM_ARCH)" \
		--target $(RPM_ARCH) \
		$(RPM_PARAMS) \
		package.spec

$(TAR): desktopeditor
	mkdir -p $(TAR_PACKAGE_DIR) common/opt/desktopeditors/app
	cp -ft common/opt/desktopeditors/app $(DESKTOP_FILES)
	tar -cz --owner=root --group=root \
		--xform=s:^common/opt:: -f"$@" common/opt

$(HELP_TAR): desktopeditor
	mkdir -p $(TAR_PACKAGE_DIR)
	tar -cI"xz -9T0" --owner=root --group=root \
		--xform=s:^common/help:: -f"$@" common/help

$(INSTALLER): $(INSTALLER_DEPENDENCY)
	cd qt-installer && ./make-install.sh

common/usr/bin/$(DESKTOPEDITORS_EXEC) : common/usr/bin/desktopeditors.m4
common/usr/bin/$(IMAGEVIEWER_EXEC) : common/usr/bin/imageviewer.m4
common/usr/bin/$(VIDEOPLAYER_EXEC) : common/usr/bin/videoplayer.m4
common/usr/share/applications/variables.m4 : branding
common/usr/share/applications/$(DESKTOPEDITORS_EXEC).desktop : common/usr/share/applications/desktopeditors.desktop.m4 common/usr/share/applications/variables.m4
common/usr/share/applications/$(IMAGEVIEWER_EXEC).desktop : common/usr/share/applications/imageviewer.desktop.m4 common/usr/share/applications/variables.m4
common/usr/share/applications/$(VIDEOPLAYER_EXEC).desktop : common/usr/share/applications/videoplayer.desktop.m4 common/usr/share/applications/variables.m4
common/usr/bin/desktopeditors : common/usr/bin/$(DESKTOPEDITORS_EXEC)
common/usr/bin/$(COMPANY_NAME_LOW) : common/usr/bin/$(DESKTOPEDITORS_EXEC)

$(BIN_FILES) $(DESKTOP_FILES) :
	m4 -I'common/usr/share/applications' $(M4_PARAMS) $< > $@

$(SYMLINK) :
	ln -srf $< $@

% : %.m4
	m4 $(M4_PARAMS)	$< > $@

%/$(PACKAGE_NAME).spec : %/package.spec 
	cp $< $@
