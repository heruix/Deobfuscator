// Deobfuscator.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "pe.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	if (argc != 2) {
		cout << "invalid arguments" << endl;
		return -1;
	}
	// Read
	PEReader::Builder builder;
	PEReader *reader = builder.setInputFilePath(argv[1])->build();
	if (reader == nullptr) {
		cout << builder.getErrMsg() << endl;
		exit(1);
	}
	PEFormat pe_fmt = reader->getPEFormat();

	// Edit
	PEEditor editor = PEEditor(pe_fmt);

	// Create new section
	char new_code[1] = { 0xC3 };
	PEEditor::SectionHeaderBuilder b = PEEditor::SectionHeaderBuilder();
	b.setName((BYTE *)string(".shadow").c_str(), 7)
		->setPointerToRawData(0xC00)
		->setSizeOfRawData(0x200)
		->setVirtualAddress(0x4000)
		->setVirtualSize(0x1)
		->setCharacteristcs(0x60000020);
	IMAGE_SECTION_HEADER shadow_section_header = b.build();

	editor.addSection(shadow_section_header, new_code, 1);
	PEFormat *modified_pe = editor.result();

	// Write
	PEWriter::Builder writer_builder;
	PEWriter *writer = writer_builder
		.setOutputFilePath("\\Users\\ogamal\\Documents\\hoge.exe")
		->setPEFormat(modified_pe)
		->build();
	if (writer == nullptr) {
		cout << writer_builder.getErrMsg() << endl;
		exit(1);
	}
	writer->write();
	return 0;
}