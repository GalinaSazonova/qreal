#include "trikGeneratorFactory.h"
#include <converters/regexpMultiConverter.h>
#include "converters/servoMotorPortConverter.h"
#include "converters/powerMotorPortConverter.h"
#include "simpleGenerators/ledGenerator.h"
#include "simpleGenerators/playToneGenerator.h"
#include "simpleGenerators/sadSmileGenerator.h"
#include "simpleGenerators/sayGenerator.h"
#include "simpleGenerators/setBackgroundGenerator.h"
#include "simpleGenerators/smileGenerator.h"
#include "simpleGenerators/systemGenerator.h"
#include "simpleGenerators/trikEnginesGenerator.h"
#include "simpleGenerators/trikEnginesStopGenerator.h"
#include "parts/trikVariables.h"

using namespace qReal::robots::generators;
using namespace simple;
using namespace trik;

TrikGeneratorFactory::TrikGeneratorFactory(qrRepo::RepoApi const &repo
		, ErrorReporterInterface &errorReporter)
	: GeneratorFactoryBase(repo, errorReporter)
{
}

TrikGeneratorFactory::~TrikGeneratorFactory()
{
}

AbstractSimpleGenerator *TrikGeneratorFactory::simpleGenerator(qReal::Id const &id
		, GeneratorCustomizer &customizer)
{
	QString const elementType = id.element();
	if (elementType == "EnginesForward" || elementType == "EnginesBackward") {
		return new TrikEnginesGenerator(mRepo, customizer, id, elementType, this);
	} else if (elementType == "EnginesStop") {
		return new TrikEnginesStopGenerator(mRepo, customizer, id, this);
	} else if (elementType == "PlayTone") {
		return new PlayToneGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Smile") {
		return new SmileGenerator(mRepo, customizer, id, this);
	} else if (elementType == "SadSmile") {
		return new SadSmileGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Say") {
		return new SayGenerator(mRepo, customizer, id, this);
	} else if (elementType == "SetBackground") {
		return new SetBackgroundGenerator(mRepo, customizer, id, this);
	} else if (elementType == "System") {
		return new SystemGenerator(mRepo, customizer, id, this);
	} else if (elementType == "Led") {
		return new LedGenerator(mRepo, customizer, id, this);
	}

	return GeneratorFactoryBase::simpleGenerator(id, customizer);
}

QString TrikGeneratorFactory::pathToTemplates() const
{
	return ":/trik/templates";
}

Binding::MultiConverterInterface *TrikGeneratorFactory::enginesConverter(bool powerMotors) const
{
	if (powerMotors) {
		return new converters::RegexpMultiConverter(converters::PowerMotorPortConverter::splitRegexp()
				, new converters::PowerMotorPortConverter);
	}

	return new converters::RegexpMultiConverter(converters::ServoMotorPortConverter::splitRegexp()
			, new converters::ServoMotorPortConverter);
}

Binding::MultiConverterInterface *TrikGeneratorFactory::enginesConverter() const
{
	return enginesConverter(true);
}

Binding::ConverterInterface *TrikGeneratorFactory::inputPortConverter() const
{
	return new Binding::EmptyConverter;
}

Binding::ConverterInterface *TrikGeneratorFactory::outputPortConverter() const
{
	return new converters::PowerMotorPortConverter;
}

void TrikGeneratorFactory::initVariables()
{
	mVariables = new parts::TrikVariables(pathToTemplates());
}
